#
# Copyright (C) 2014 Cloudius Systems, Ltd.
#
# This work is open source software, licensed under the terms of the
# BSD license as described in the LICENSE file in the top-level directory.
#

provides = ['java']

from osv.modules.filemap import FileMap
from osv.modules import api

api.require('fonts')

usr_files = FileMap()

usr_files.add('${OSV_BASE}/apps/openjdk8-fedora/install/usr/lib/jvm/jre') \
         .to('/usr/lib/jvm/jre') \
         .exclude('lib/audio/**') \
         .exclude('lib/security/cacerts')

