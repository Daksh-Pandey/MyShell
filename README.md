# MyShell
### Tech-stack:
* C
* Makefile

MyShell is a Linux command line shell based on Bash. Two options under a command have been covered in addition to the functionality of the command without any options. If any other options/commands are inputted, MyShell outputs that the given option/command is invalid/not implemented. Unlike real world shells, MyShell cannot execute more than one options in a single line. The description of the commands are as follows-
* **[echo](/shell.c)** – It outputs given string in the next line. Strings containing spaces are to be specified in double quotes (“”).
  * **-n** – prints given string without the trailing newline.
  * **--help** – output this help and exit.
* **[pwd](/shell.c)** – outputs the path of the current directory.
  * **-P** – avoid using symlinks to display the current directory.
  * **--help** – outputs text that explains the working and options of MyShell’s pwd.
* **[cd](/shell.c)** – changes the current directory. If it fails to do so, it outputs that. “~” and “/” specify “HOME” and “ROOT” respectively.
  *	**-L** – follows symlinks (but restricted to paths where last argument in the path of a given directory is a symlink).
  *	***-P** – does not follow symlinks (no symlink should be given in the path of the directory). This constriction arises due to the nature of chdir() function.
* **[ls](/ls.c)** – lists all the files and folders in a given directory. If no argument is passed, it displays contents of the current directory. If directory could not be opened, it displays the corresponding error.
  * **-A** – displays hidden files and folders (starting with “.”).
  *	**-1** – displays name of each file and folder separately in a newline.
* **[cat](/cat.c)** – concatenates contents of files and prints them to standard output. An error message is thrown when no file has been specified or the given file could not be found. (MyShell’s cat command can’t be used to make new files using “>”).
  *	**-n** – outputs the content of the files along with the line number.
  * **-E** – prints “$” when a newline is encountered.
*	**[date](/date.c)** – displays the current date and time of the system (local) if no argument is specified.
  *	**-u** – displays the current Coordinated Universal Time (UTC).
  *	**-r** – displays the last modified date and time of the given file. Error message is thrown if the file could not be found or if too many arguments are passed.
* **[rm](/rm.c)** – removes the given files. If no file is specified, it tells the user to specify a file.
  * **-i** – prompts the user before removing each file. It throws an error if the specified file is in fact a directory, if the file doesn’t exist, or if the file is write protected.
  * **-d** – removes an empty directory. It throws an error if the specified directory is in fact not a directory, if the directory doesn’t exist, if the directory is write protected, or if the directory is not empty.
* **[mkdir](/mkdir.c)** – creates an empty directory whose protection can be specified. It throws an error if the given directory already exists.
  * **-v** – prints a message for each created directory (verbose).
  * **-m** – set protection mode of the directory. By default, read, write and search accesses are given. In MyShell, four types of protection modes are covered-
    * **-m=r** – only read access is provided.
    * **-m=w** – only write access is provided.
    * **-m=x** – only search access is provided.
    * **-m=rwx** – read, write and search accesses are provided (same as -m).
