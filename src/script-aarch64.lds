SECTIONS {

	/* Align sections to keep PE tools happy */
	alignment = 512;

	/* Virtual addresses start at 0x20000 */
	. = 0x20000;
	_start = .;

	/* bzImage prefix */
	_prefix_pos = 0;
	.prefix : AT ( _prefix_pos ) {
		_prefix = .;
		*(.prefix)
		*(.prefix.*)
		. = ALIGN ( alignment );
		_eprefix = .;
	}
	_prefix_len = ABSOLUTE ( _eprefix ) - ABSOLUTE ( _prefix );

	/* text section */
	_text_pos = ( _prefix_pos + _prefix_len );
	.text : AT ( _text_pos ) {
		_text = .;
		*(.text)
		*(.text.*)
		_etext = .;
		_data = .;
		*(.rodata)
		*(.rodata.*)
		*(.data)
		*(.data.*)
		. = ALIGN ( alignment );
		_edata = .;
		_etext = .;
	}
	_text_len = ABSOLUTE ( _etext ) - ABSOLUTE ( _text );
	_data_len = ABSOLUTE ( _edata ) - ABSOLUTE ( _data );

	/* bootmgr.exe hardcodes the address 0x30000 for use as a
	 * buffer accessible by real-mode code.  We can't fit our
	 * .text, .data, and .bss below this region, so explicitly
	 * place the .bss higher in memory.
	 */
	_forbidden_start = 0x30000;
	_forbidden_end = 0x40000;

	/* Uninitialised data section */
	.bss ( NOLOAD ) : {
		_bss = .;
		ASSERT ( ABSOLUTE ( . ) <= ABSOLUTE ( _forbidden_start ),
			 "Binary is too large" );
		. = ABSOLUTE ( _forbidden_end );
		*(.bss)
		*(.bss.*)
		*(COMMON)
		*(.stack)
		*(.stack.*)
		. = ALIGN ( alignment );
		_ebss = .;
	}
	_bss_len = ABSOLUTE ( _ebss ) - ABSOLUTE ( _bss );

	/* Secure Boot Advanced Targeting (SBAT) section */
	_sbat_pos = ( _text_pos + _text_len );
	.sbat : AT ( _sbat_pos ) {
		_sbat = .;
		*(.sbat)
		*(.sbat.*)
		_msbat = .;
		. = ALIGN ( alignment );
		_esbat = .;
	}
	_sbat_used = ABSOLUTE ( _msbat ) - ABSOLUTE ( _sbat );
	_sbat_len = ABSOLUTE ( _esbat ) - ABSOLUTE ( _sbat );

	/* Relocations section */
	_reloc_pos = ( _sbat_pos + _sbat_len );
	_reloc = .;

	_end = .;

	_text_total_len = ( _text_len );
	_data_total_len = ( _data_len );
	_bss_total_len = ( _bss_len );

	/* Symbols required by i386.x86_64 objects */
	__i386__start = _start;
	__i386__end = _end;

	/DISCARD/ : {
		*(.comment)
		*(.comment.*)
		*(.note)
		*(.note.*)
		*(.eh_frame)
		*(.eh_frame.*)
		*(.rel)
		*(.rel.*)
	}
}
