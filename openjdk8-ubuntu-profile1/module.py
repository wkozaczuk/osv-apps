#
# Copyright (C) 2014 Cloudius Systems, Ltd.
#
# This work is open source software, licensed under the terms of the
# BSD license as described in the LICENSE file in the top-level directory.
#

from osv.modules.filemap import FileMap
from osv.modules import api
import os, os.path

provides = ['java']

api.require('fonts')
api.require('ca-certificates')
api.require('libz')
api.require('josvsym')
api.require('httpserver-jolokia-plugin')
api.require('httpserver-jvm-plugin')

usr_files = FileMap()
usr_files.add('${OSV_BASE}/apps/openjdk8-ubuntu-profile1/install').to('/').allow_symlink()
usr_files.add('${OSV_BASE}/apps/openjdk8-ubuntu-profile1/install/usr/lib/jvm/java') \
    .to('/usr/lib/jvm/java') \
    .allow_symlink()
usr_files.link('/usr/lib/jvm/jre').to('/usr/lib/jvm/java/jre')
