#!/bin/sh

if [ ! -d "track_chip.db" ]; then
	sqlite3 track_chip.db -cmd ".read track_chip.sql" ".quit"
fi