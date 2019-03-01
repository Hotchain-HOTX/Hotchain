
Debian
====================
This directory contains files used to package hotchaind/hotchain-qt
for Debian-based Linux systems. If you compile hotchaind/hotchain-qt yourself, there are some useful files here.

## hotchain: URI support ##


hotchain-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install hotchain-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your hotchainqt binary to `/usr/bin`
and the `../../share/pixmaps/hotchain128.png` to `/usr/share/pixmaps`

hotchain-qt.protocol (KDE)

