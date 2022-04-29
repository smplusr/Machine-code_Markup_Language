input="$*"
if [ -z "$1" ]
then
	echo	"No argument provided, reading keyboard"
	echo	"Enter Netwide Assembly Input:"
	read	input
fi

touch	"a.S"
#echo	".intel_syntax noprefix" >> "a.S"
echo	$input >> "a.S"

as	-msyntax=intel -mnaked-reg -o a.o a.S
ld	-Ttext 0 -o a.elf a.o
objdump	-d a.elf
rm	-rf a.S a.o a.elf
