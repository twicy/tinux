# Generl Setup for the Kernel

- Platform: x86, 32-bit 80386 processor
- Boot Loader: GRUB, with multiboot support
  - Advantage: after GRUB loading the kernel into memory, we will already be in `Protected Mode`, not `Real Mode`
- Acknowledgement:
  - Huan Liu and his amazing tutorial: [http://wiki.0xffffff.org/](http://wiki.0xffffff.org/)
  - Mr. James Molly, the Genesis of this kernel, [http://www.jamesmolloy.co.uk/tutorial_html/](http://www.jamesmolloy.co.uk/tutorial_html/)

## Purpose

- The purpose of this project is to be familiar with the very fundamentals of the Operating System:
  - History Legacy: such as, Real Mode
  - Memory Management: segment and paging

