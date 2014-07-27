ipaddrutil
==========
Miscellaneous IP address utilities

## Installation
In the future, I should probably create a [Homebrew tap](https://github.com/Homebrew/homebrew/wiki/brew-tap) at some point in the future.

## `getifaddrs`
Get IP addresses, in a parseable format

Outputs the IP addresses for the system. It shows all interfaces by default. Internally, it uses `getifaddrs` to get the addresses (hence the name). Passing a nonexistant interface does not error but does not output anything. Passing a single parameter will filter the output to that interface only.

The name is awkward, but I couldn't think of anything else, and it fits as it uses the eponymous call internally. I'm open to suggestions.

## License
Copyright 2014 Joshua Oldenburg, released under the MIT license.
