import argparse
parser = argparse.ArgumentParser(description="converts a text file to a multiline string, with newlines inside each string")
parser.add_argument("input", help="The file to convert")
parser.add_argument("output",
                    help="Output file. Uses input file.conv by default.",
                    nargs='?')

args = parser.parse_args()


def convert_line(line):
    line = line.replace('"', '\\"')
    line = '"' + line[:-1] + "\\n" + '"\n'
    return line


def convert_file(input, output):
    with open(input, "r") as inp, open(output, "w") as out:
        for line in inp.readlines():
            out.write(convert_line(line))

if __name__ == '__main__':
    if not args.output:
        args.output = args.input + ".conv"

    convert_file(args.input, args.output)
