#!/usr/bin/env python

import getpass, fileinput, os
from sys import stdin, stdout, stderr, exit

def intro_screen():
    os.system('clear')
    stdout.write( "Welcome to Escape!\n" )
    stdout.write( "To read the instructions, press i.\n")
    stdout.write( "To start the game, press s.\n")
    selectedOption = raw_input('==> ')
    return selectedOption
    
def instruction_screen():
    os.system('clear')
    try:
	open("instructions")
	stdin = file("instructions")
    except:
	stderr.write("instructions does not exist\n")
	exit(1)
    for line in stdin:
	stdout.write(line)
    stdout.write( "Press any key to return to the opening screen.\n")
    if raw_input('==> '):
        selectedOption = 'b'
    else:
        selectedOption = 'i'
    return selectedOption
    
def start_game():
    os.system('clear')
    try:
        open(storyName)
        stdin = file(storyName)
    except:
        stderr.write(storyName + " does not exist./n")
        exit(1)
    for line in stdin:
        stdout.write(line)
    stdout.write( "Press any key to end the game./n")
    if raw_input('==> '):
        return 'e'
    else:
        return 's'
    

if __name__=='__main__':
    state = 'b'
    stdout.write( "\nHello, %s!" % (getpass.getuser()))
    stdout.write( "\nPlease input a story file: ")
    storyName = raw_input()
    while(1):
        if state == 'b':
            state = intro_screen()
        if state == 'i':
            state = instruction_screen()
        if state == 's':
            state = start_game()
        if state == 'e':
            break
    
    exit(0)
