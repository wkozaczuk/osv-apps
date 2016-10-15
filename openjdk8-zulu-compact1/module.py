#
# Copyright (C) 2016 Waldemar Kozaczuk
#
# This work is open source software, licensed under the terms of the
# BSD license as described in the LICENSE file in the top-level directory.
#

from osv.modules.filemap import FileMap
from osv.modules import api
import os, os.path

provides = ['java']

non_isolated_jvm = True

api.require('fonts')
api.require('ca-certificates')
api.require('libz')
api.require('josvsym')

usr_files = FileMap()
usr_files.add('${OSV_BASE}/apps/openjdk8-zulu-compact1/install').to('/').allow_symlink()
usr_files.add('${OSV_BASE}/apps/openjdk8-zulu-compact1/install/usr/lib/jvm/java') \
    .to('/usr/lib/jvm/java') \
    .allow_symlink()
usr_files.link('/usr/lib/jvm/jre').to('/usr/lib/jvm/java/jre')
