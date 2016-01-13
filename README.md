# openmediavault-abcde

[![Build Status](https://travis-ci.org/zvecr/openmediavault-abcde.svg?branch=master)](https://travis-ci.org/zvecr/openmediavault-abcde)

abcde plugin for OpenMediaVault

## manual install

apt-get install abcde python-musicbrainz2 libmusicbrainz-discid-perl libwebservice-musicbrainz-perl lame flac eject

copy files

source /usr/share/openmediavault/scripts/helper-functions && omv_purge_internal_cache
service openmediavault-engined restart

udevadm control --reload-rules
udevadm trigger

## todo

expose logging
move abcde.conf to home instead of /etc/
add release .deb handling
add block for single instance omv-abcde
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