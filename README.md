# hello-x86_64

This image is a precursor to the development of a new 64-bit OS.  The
image runs as a standalone application on a 64-bit X86 machine.  The
image will dump some output and then present the user with a simple
echo command line.  You can type anything and it will be echo'd back to
you.  The image is setup to run in a qemu virtual machine.  It uses
simple UART access to send and receive characters from the user.

This code is based on https://github.com/winksaville/baremetal-x86_64
but has been modified quite a bit.  Even so I've included the required
Apache license document as required.

To run this you will need to have xorriso and qemu installed on your
Linux distro.  For Ubuntu you can do this:

```
$ sudo apt-get install xorriso qemu
```

One you have these installed you can type:

```
$ make run
```
