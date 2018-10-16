package demo

import java.io.File
import java.net.InetSocketAddress
import java.nio.file.Files
import java.nio.file.attribute.{PosixFileAttributeView, PosixFilePermissions}

import akka.actor._
import akka.io.{IO, Tcp}
import akka.util.ByteString

import scala.io.{Source, StdIn}

/**
  * Created by wkozaczuk on 10/16/18.
  */
// http://doc.akka.io/docs/akka/snapshot/scala/io.html
// http://doc.akka.io/docs/akka/snapshot/dev/io-layer.html#io-layer

// Concepts:
// -- manager actor - val manager = IO(Tcp) // or IO(Udp) etc or IO(Http)
// -- worker actor (for example representing given connection) - presents itself via Connected message
// ---->   manager ! Connect
// ---->   sender receives Connected

// "The manager receives I/O command messages and instantiates worker actors in response. The worker
// actors present themselves to the API user in the reply to the command that was sent. For example after a
// Connect command sent to the TCP manager the manager creates an actor representing the TCP connection.
// All operations related to the given TCP connections can be invoked by sending messages to the connection
// actor which announces itself by sending a Connected message."

// ByteString

// "The manager actor creates (and therefore supervises) the selector actors, which in turn create and
// supervise their channel actors. The actor hierarchy of one single transport implementation therefore
// consists of three distinct actor levels, with the management actor at the top-, the channel actors
// at the leaf- and the selector actors at the mid-level."

// Concepts:
// -- manager actor - val manager = IO(Tcp) // or IO(Udp) etc or IO(Http)
// -- selector actor
// -- channel actors
// -----> manager actor --> selector actor --> channel actor (worker)

object FileServiceConnectionHandler {
  def props(remote: InetSocketAddress, connection: ActorRef): Props =
    Props(new FileServiceConnectionHandler(remote, connection))
}

class FileServiceConnectionHandler(remote: InetSocketAddress, connection: ActorRef) extends Actor with ActorLogging {

  // We need to know when the connection dies without sending a `Tcp.ConnectionClosed`
  context.watch(connection)
  sendHelp()

  def receive: Receive = {
    case Tcp.Received(data) =>
      val text = data.utf8String.trim
      handleCommand(text,sender())

    case _: Tcp.ConnectionClosed =>
      println(s"Stopping, because connection for remote address $remote closed")
      context.stop(self)

    case Terminated(`connection`) =>
      println(s"Stopping, because connection for remote address $remote died")
      context.stop(self)
  }

  private def fileLine(f:File):String = {
    val attr = Files.getFileAttributeView(f.toPath,classOf[PosixFileAttributeView]).readAttributes()
    val entryType = if(attr.isSymbolicLink) "l" else if(attr.isDirectory) "d" else "-"
    val permissions = PosixFilePermissions.toString(attr.permissions())
    val entriesCount = Option(f.listFiles()).map(_.length).getOrElse(1)
    val owner = attr.owner().getName
    val group = attr.group().getName
    f"$entryType%s$permissions%s $entriesCount%3d $owner%s ${attr.size()}%10d $group%s ${attr.lastModifiedTime()}%s ${f.getName}%s"
  }

  private def sendHelp() = {
    connection ! Tcp.Write(ByteString(s"------------------------------------------!\n"))
    connection ! Tcp.Write(ByteString(s"Type `bye` to disconnect!\n"))
    connection ! Tcp.Write(ByteString(s"Type `dir:<path>` to list directory!\n"))
    connection ! Tcp.Write(ByteString(s"Type `file:<path>` to list content of file!\n"))
    connection ! Tcp.Write(ByteString(s"Type `help` to see it again!\n"))
    connection ! Tcp.Write(ByteString(s"------------------------------------------!\n"))
  }

  private def handleCommand(text:String,writer:ActorRef):Unit = {

    val ByeCommandRegex = """(?i)bye""".r
    val HelpCommandRegex = """(?i)help""".r
    val ListDirectoryCommandRegex = """(?i)dir:(.+)""".r
    val GetFile = """(?)file:(.+)""".r

    text match {
      case ByeCommandRegex() =>
        println(s"@$remote: Requested to disconnect ...")
        writer ! Tcp.Write(ByteString("Bye too\n"))
        context.stop(self)

      case HelpCommandRegex() =>
        sendHelp()

      case ListDirectoryCommandRegex(directoryPath) =>
        println(s"@$remote: Requested to list directory $directoryPath")
        val directory = new File(directoryPath)
        (directory.isDirectory, directory.exists()) match {
          case (true, true) =>
            directory.listFiles().toList.
              sortBy(_.getName).
              map(fileLine).
              foreach(line => writer ! Tcp.Write(ByteString(s"$line\n")))
          case (_, _) =>
            writer ! Tcp.Write(ByteString(s"Directory $directoryPath does not exits or is not a directory"))
        }

      case GetFile(filePath) =>
        println(s"@$remote: Requested to fetch file $filePath")
        val file = new File(filePath)
        (file.isFile, file.exists()) match {
          case (true, true) =>
            Source.fromFile(file).
              getLines().
              foreach(line => writer ! Tcp.Write(ByteString(s"$line\n")))

          case (_, _) =>
            writer ! Tcp.Write(ByteString(s"File $filePath does not exits or is not a file\n"))
        }

      case other =>
        val response = s"@$remote: Received unrecognized command: $other"
        writer ! Tcp.Write(ByteString(s"$response\n"))
        println(response)
    }
  }
}

object FileService {
  def props(endpoint: InetSocketAddress): Props =
    Props(new FileService(endpoint))
}

class FileService(endpoint: InetSocketAddress) extends Actor with ActorLogging {

  import context._
  IO(Tcp) ! Tcp.Bind(self, endpoint)

  override def receive: Receive = {
    case Tcp.Connected(remote, _) =>
      println(s"Remote address $remote connected")
      sender ! Tcp.Register(context.actorOf(FileServiceConnectionHandler.props(remote, sender)))
  }
}

object FileServiceApp extends App {

  val system = ActorSystem("file-service-system")
  val endpoint = new InetSocketAddress("localhost", 1055)
  system.actorOf(FileService.props(endpoint), "file-service")

  StdIn.readLine("Hit ENTER to exit ...\n")
  system.terminate()
}
