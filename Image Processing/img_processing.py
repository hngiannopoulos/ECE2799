#!/usr/bin/env python

import Image
from argparse import ArgumentParser
import os.path

# size for output image
dpi = 200.0
outImg_w = int(6.49 * dpi) 
outImg_h = int(4.13 * dpi)

# Checks to see if a filename is valid 
def is_valid_file(parser, arg):
    if not os.path.exists(arg):
        parser.error("The file %s does not exist!" % arg)
    else:
        return open(arg, 'rb')  # return an open file handle

def main():
	# Open the image
	# im = Image.open("img.jpg")
	# im = Image.open("test2.png")
	im = Image.open(args.filename)

	# Get pixel data for callibration point
	callibrateImg = Image.open("calibrationPoint.png")
	# callibrateImg = callibrateImg.getdata()

	print "Imput Image Details: "
	print "Size (X, Y): ", im.size
	print "Format: ", im.format
	print "Color Mode: ", im.mode

	out = open(args.filename.name[0:-3] + "ECE", "wb+")

	# Resize and convert to greyscale for sd card
	sd_img = im.resize((args.x_pos, args.y_pos), 3).convert('1')

	# Resize and convert image for printing 
	out_img = im.resize((outImg_w, outImg_h), 3)

	# copy data onto new image
	# left upper, right lower
	out_x, out_y = out_img.size

	# Copy into top left
	x, y = callibrateImg.size
	out_img.paste(callibrateImg, (0, 0, x, y))

	# Copy into top right
	callibrateImg = callibrateImg.rotate(270)
	x, y = callibrateImg.size
	out_img.paste(callibrateImg, (out_x - x , 0, out_x , y))

	# copy bottom right
	callibrateImg = callibrateImg.rotate(270)
	x, y = callibrateImg.size
	out_img.paste(callibrateImg, (out_x - x , out_y - y, out_x , out_y))

	# copy bottom left
	callibrateImg = callibrateImg.rotate(270)
	x, y = callibrateImg.size
	out_img.paste(callibrateImg, (0 , out_y - y, x, out_y))



	out_img.save(open("out.jpg", "wb+"))

	# option to save the image sent to the sd card
	# sd_img.save(open("sdout.jpg", "w+"))

	print sd_img.size
	# write data to the output file
	# out.write(str(args.x_pos))
	# out.write(',')
	# out.write(str(args.y_pos))
	out.write(sd_img.tostring())
	out.close()

parser = ArgumentParser(description='Converts Images for use with the Haptic Feedback System')

parser.add_argument("-i", dest="filename", required=True,
                    help="input image file", metavar="FILE",
                    type=lambda x: is_valid_file(parser, x))

parser.add_argument('--width', dest='x_pos', action='store',
					default=160,
                   help='Width Value')

parser.add_argument('--height', dest='y_pos', action='store',
					default=96,
                   help='Height Value')

args = parser.parse_args()



if __name__ == '__main__':
	main()

