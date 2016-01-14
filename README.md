# openmediavault-abcde

[![Build Status](https://travis-ci.org/zvecr/openmediavault-abcde.svg?branch=master)](https://travis-ci.org/zvecr/openmediavault-abcde)

abcde plugin for OpenMediaVault

## install

curl -o- https://github.com/zvecr/openmediavault-abcde/../openmediavault-abcde.release.deb | dpkg --install 

## manual install

apt-get install abcde python-musicbrainz2 libmusicbrainz-discid-perl libwebservice-musicbrainz-perl lame flac eject

copy all files to root of file system

/debian/postinst configure
source /usr/share/openmediavault/scripts/helper-functions && omv_purge_internal_cache
service openmediavault-engined restart

udevadm control --reload-rules
udevadm trigger

## todo

expose logging
add release .deb handling
add extra cmd line options for abcde
check packaging
    chmod +x for scripts

### later

cddb selection
additional output types
additional quality selection
local cddb edditor
cddb proxy support
track comments