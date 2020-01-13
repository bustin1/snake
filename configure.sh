#!/bin/bash

if [ -f /etc/redhat-release ]; then
  sudo yum install libsdl2-dev # graphics, drawing
  sudo yum install libsdl2-image-dev # images
  sudo yum install libsdl2-ttf-dev # fonts
fi

if [ -f /etc/lsb-release ]; then
  sudo apt-get install libsdl2-dev # graphics, drawing
  sudo apt-get install libsdl2-image-dev # images
  sudo apt-get install libsdl2-ttf-dev # fonts
fi

echo ""
echo "Remember to change the paths to \"SnakeAllTime.txt\" and your \"[name of font].ttf\" 
in main.cpp and Window.cpp respectively!"
echo ""
