# 0x03. Python - /proc filesystem

## Learning Objectives
* What is the `/proc filesystem`
* What is the `/proc/maps` file
* What is the `/proc/mem` file
* What is the link between those two files
* How does the virtual memory map into the RAM

## Requirements
* Allowed editors: `vi`, `vim`, `emacs`
* All your files will be interpreted/compiled on Ubuntu 14.04 LTS using `python3` (version 3.4.3)
* All your files should end with a new line
* The first line of all your files should be exactly `#!/usr/bin/python3`
* A `README.md` file, at the root of the folder of the project, is mandatory
* Your code should use the `PEP 8` style
* All your files must be executable
* The length of your files will be tested using `wc`

---

### [0. Hack the VM](./read_write_heap.py)
Write a script that finds a string in the heap of a running process, and replaces it.

* Usage: `read_write_heap.py pid search_string replace_string`
	* where `pid` is the pid of the running process
	* and strings are ASCII
* The script should look only in the heap of the process
* Output: you can print whatever you think is interesting
* On usage error, print an error message on `stdout` and exit with status code `1`
