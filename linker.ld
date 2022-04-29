SECTIONS
{
	. = 0x7c00;
	.text : {
		_text = .;
		* (*);
		_text_end = .;
	}

	.fill : { FILL (0x0); }
	. = 0x7dfe;
	.end : { SHORT (0xaa55) }
}

