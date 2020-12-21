#!/usr/bin/env python
#encoding: utf-8;

'''
Fuzzing Test 001
'''

from pwn import *
import sys, os, subprocess
import random
import time, datetime
import argparse
import threading

FILENAME = "./a.out"
LIBCNAME = ""
LOGDEFNAME = "./log.log"

hosts = ("","localhost","localhost")
ports = (0,12300,23947)
rhp1 = {'host':hosts[0],'port':ports[0]}    #for actual server
rhp2 = {'host':hosts[1],'port':ports[1]}    #for localhost
rhp3 = {'host':hosts[2],'port':ports[2]}    #for localhost running on docker
context(os='linux',arch='amd64')
libc = ELF(LIBCNAME) if LIBCNAME!="" else None

## log utilities #########################################

global silent,alive

silent = False
alive = True

def wlog(msg):
  global _f
  if not silent:
    print(msg)
  _f.write(msg + "\n")

def start_log(outputname):
  global _f
  global stime
  _f = open(outputname, "w")
  stime = time.time()
  wlog("xxx Start of fuzzing xxx")
  wlog("bin:        {}".format(FILENAME))
  wlog("start time: {}".format(datetime.datetime.now()))
  wlog("-----------------------------")

def end_log():
  global _f
  global stime
  wlog("\n----------------------------")
  wlog("xxx End of fuzzing xxx")
  wlog("total time: {}".format(time.time() - stime))
  _f.close()

def l(msg, *args):
  _msg = msg + "("
  for a in args:
    _msg += "{}, ".format(a)
  _msg += ")"
  wlog(_msg)

def killer():
  global timelimit, alive
  sleep(timelimit)
  alive = False

def initState():
  global alive
  global counter, w, h
  alive = True
  h = random.randint(2, 50)
  w = random.randint(2, 50)
  counter = random.randint(0, 2**(h*w))

## end of log utilities #################################


## utilities ###########################################

def hoge(ix):
  global c
  pass


## exploit ###########################################

def genpay(w, h):
  global counter
  pay = b""
  for row in range(h):
    for col in range(w):
      if(bin(counter)[2:].rjust(w*h)[row*w+col]=="1"):
        pay += "#"
      else:
        pay += "."
    pay += "\n"
  counter += 1
  pay = b"." + pay[1:]
  pay = pay[:-2] + b"."
  return pay

def execbin():
  global c
  global counter, w, h

  pay = genpay(w, h)

  print("sending {} {}".format(h,w))
  print(pay)
  c.sendline("{} {}".format(h,w))
  c.sendline(pay)
  print("Answer: {}".format(c.recvline()))
  return

## main ##############################################

if __name__ == "__main__":
    global c
    global silent
    global timelimit
    global counter, w, h

    '''
    counter = 0
    w = 2
    h = 2
    '''

    # parse args
    ap = argparse.ArgumentParser()
    ap.add_argument('--silent', action='store_const', const=True)
    ap.add_argument('-o', '--output', type=str, help="Output filename", default=LOGDEFNAME)
    ap.add_argument('-t', '--timelimit', type=int, help="Timelimit per single execution (prevent deadlock)", default=1)
    ap.add_argument('host', type=str, help="Host to run binary", default="l")
    args = ap.parse_args()
    _host = args.host
    _outputname = args.output
    silent = args.silent
    timelimit = args.timelimit

    # do my business
    start_log(_outputname)
    while True:
      # choose host
      if _host == "l":
        c = remote(rhp2['host'],rhp2['port'])
      elif _host == "v":
        c = remote(rhp3['host'],rhp3['port'])
      elif _host == "r":
        c = remote(rhp1['host'],rhp1['port'])
      elif _host == "p":
        c = process("./a.out")

      # set time limit
      t = threading.Thread(target=killer)
      t.start()

      try:
        initState()
        execbin()
        '''
        if counter >= 2**(w*h):
          w += 1
          counter = 0
          if(w > 50):
            w = 2
            h += 1
            if(h > 50):
              print("[!] All tests passed!!")
              exit(0)
        '''
      except:
        wlog("\n")
        wlog("System Dead: {}".format(sys.exc_info()))
        end_log()
        exit(0)

      c.close()