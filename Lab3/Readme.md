# Section 1
Script is in this Directory.

when the new terminal opens it sees the variables i appended in the .bashrc,

because .bashrc will run automatically with each new bash shell
# Section 2
1- ls /usr/bin > /tmp/commands.list

2- This worked only in the case of logining in from TTY (ctrl + ALT + F3) !!

3- ls /usr/bin/ | wc -l //Returns 1509 which is the number of lines == no of commands

4-
    a- Prints content of file2
    b- Error : Missing Operand
    c- Prints 1 which is the line of the file name /etc/passwd

5-sudo find / -iname .profile 

6-ls -i / /etc /etc/hosts

7-sudo ln -s /etc/passwd /boot/SymbolicLink

8-in /boot/ it's done successfuly, while in /boot/efi i couldn't , Because Hardlinks doesn't work across different partitions !

9-The '>' is called the secondary prompt string , it indicates that the echo is waiting for more input 
To Change it you can edit the variable PS2 where '>' is stored 
ex : PS2=":"