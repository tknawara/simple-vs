project('bison-tut', 'c')
bison = find_program('bison')
flex = find_program('flex')
glibdep = dependency('glib-2.0')

gen_flex_src = custom_target('flex',
			     input : ['lexer.l'],
			     output : ['lexer.c', 'lexer.h'],
			     command : [flex, '@INPUT@'])

gen_bison_src = custom_target('bison',
			      input : ['parser.y'],
			      output : ['parser.c', 'parser.h'],
			      command : [bison, '@INPUT@'])
			     
executable('sasm',
	   'main.c', 'command.c', 'command.h',
	   gen_flex_src, gen_bison_src,
	   dependencies : glibdep)
