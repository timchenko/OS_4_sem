#!/bin/sh
find -L -type l -mmin +$(( 7*24*60 ))
