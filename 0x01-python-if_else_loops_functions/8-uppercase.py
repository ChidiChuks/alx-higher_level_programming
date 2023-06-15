#!/usr/bin/python3
# 8-uppercase.py

def uppercase(string):
     for char in string:
         print(chr(ord(char) - 32), end=" ")
         print()
