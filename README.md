# openmediavault-abcde

[![Build Status](https://travis-ci.org/zvecr/openmediavault-abcde.svg?branch=master)](https://travis-ci.org/zvecr/openmediavault-abcde)

abcde plugin for OpenMediaVault

## manual install

apt-get install abcde python-musicbrainz2 libmusicbrainz-discid-perl libwebservice-musicbrainz-perl lame flac eject

copy files

source /usr/share/openmediavault/scripts/helper-functions && omv_purge_internal_cache
service openmediavault-engined restart
