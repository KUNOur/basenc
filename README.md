Basenc
======

Basenc is a library used to encode data into a human-readable encoding format.

Supported Encodings
-------------------

- Base32

How to Build
------------

This project can use GNU Autotools to build itself. To create the proper
configuration scripts, run

	autoreconf -iv

or

	./buildprep

You should then be able to build this with the standard

	./configure
	make
	make install

This project can also use the CMake build system. To build the basenc library
(libbasenc), do the following in the top-level directory:

	mkdir build
	cd build
	cmake ..
	make

base32enc
---------

There is an included command-line tool (called "base32enc") that can be used to
encode data to Base32. It can be used either from the command line (send an EOF
character ^D to stop) or it can encode a file. Its output will always be sent to
stdout.

License
-------

Copyright 2013 David Jackson

This program is distributed under the GNU Lesser General Public License
(LGPL) version 3. Thhe text of this license is included in the LICENSE
file and can be found online
[here](https://www.gnu.org/licenses/lgpl-3.0-standalone.html). The base GPLv3
can be found in LICENSE.GPL or online
[here](https://www.gnu.org/licenses/gpl-3.0-standalone.html).
