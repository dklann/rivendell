#!%PYTHON_BANGPATH%

# pypad_live365.py
#
# Write PAD updates to Live365 stations
#
#   (C) Copyright 2018 Fred Gleason <fredg@paravelsystems.com>
#
#   This program is free software; you can redistribute it and/or modify
#   it under the terms of the GNU General Public License version 2 as
#   published by the Free Software Foundation.
#
#   This program is distributed in the hope that it will be useful,
#   but WITHOUT ANY WARRANTY; without even the implied warranty of
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#   GNU General Public License for more details.
#
#   You should have received a copy of the GNU General Public
#   License along with this program; if not, write to the Free Software
#   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
#

import sys
import syslog
import configparser
import pycurl
import PyPAD
from io import BytesIO

def eprint(*args,**kwargs):
    print(*args,file=sys.stderr,**kwargs)

def ProcessPad(update):
    n=1
    try:
        while(True):
            section='Station'+str(n)
            if update.shouldBeProcessed(section) and update.hasPadType(PyPAD.TYPE_NOW):
                member=update.escape(update.config().get(section,'MemberName'),PyPAD.ESCAPE_URL)
                password=update.escape(update.config().get(section,'Password'),PyPAD.ESCAPE_URL)
                title=update.resolvePadFields(update.config().get(section,'TitleString'),PyPAD.ESCAPE_URL)
                artist=update.resolvePadFields(update.config().get(section,'ArtistString'),PyPAD.ESCAPE_URL)
                album=update.resolvePadFields(update.config().get(section,'AlbumString'),PyPAD.ESCAPE_URL)
                seconds=str(update.padField(PyPAD.TYPE_NOW,PyPAD.FIELD_LENGTH)//1000)
                buf=BytesIO()
                curl=pycurl.Curl()
                url='http://www.live365.com/cgi-bin/add_song.cgi?member_name='+member+'&password='+password+'&version=2&filename=Rivendell&seconds='+seconds+'&title='+title+'&artist='+artist+'&album='+album
                curl.setopt(curl.URL,url)
                curl.setopt(curl.WRITEDATA,buf)
                curl.setopt(curl.FOLLOWLOCATION,True)
                try:
                    curl.perform()
                    code=curl.getinfo(pycurl.RESPONSE_CODE)
                    if (code<200) or (code>=300):
                        syslog.syslog(syslog.LOG_WARNING,'['+section+'] returned response code '+str(code))
                except pycurl.error:
                    syslog.syslog(syslog.LOG_WARNING,'['+section+'] failed: '+curl.errstr())
                curl.close()
            n=n+1

    except configparser.NoSectionError:
        return

#
# 'Main' function
#
syslog.openlog(sys.argv[0].split('/')[-1])

rcvr=PyPAD.Receiver()
try:
    rcvr.setConfigFile(sys.argv[3])
except IndexError:
    eprint('pypad_live365.py: you must specify a configuration file')
    sys.exit(1)
rcvr.setCallback(ProcessPad)
rcvr.start(sys.argv[1],int(sys.argv[2]))