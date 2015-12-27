ipaddrutil
==========
Miscellaneous IP address utilities

## Installation
In the future, I should probably create a [Homebrew tap](https://github.com/Homebrew/homebrew/wiki/brew-tap) at some point in the future.

Run `make all` to build the scripts, then move them to `/usr/local/bin` or another location in your path.

## `getifaddrs`
Get IP addresses, in a parsable format

Outputs the IP addresses for the system. It shows all interfaces by default. Internally, it uses `getifaddrs` to get the addresses (hence the name). Passing a nonexistent interface does not error but does not output anything. Passing a single parameter will filter the output to that interface only. Passing `-q` outputs only the IP address, not the interface.

The name is awkward, but I couldn't think of anything else, and it fits as it uses the eponymous call internally. I'm open to suggestions.

## `getipfortmux`
Get the dynamic IP address of en0, intended for my specific tmuxline setup (see JoshTheGeek/dotfiles)

Currently, the only difference between a typical commercial network and the home network is that an H is appended to the IP at home. Eventually I might fetch the public IP and display that, but that will likely be rather slow for a tmux status bar. If there is no DHCP address for some reason, then it prints the home static IP appended with ND. Also, when there is no network, it outputs "no network".

This has hardcoded the WiFi interface of my laptop and ignoring my static IP. (I have en1 set with both a static IP that I use at home and a DHCP IP that I use elsewhere so I don't have to switch when I switch networks.) You probably shouldn't use this without modification. The constants are all in the header of the file, but without my specific setup it will not be overly useful.

## License
Copyright 2014 Joshua Oldenburg, released under the MIT license.
