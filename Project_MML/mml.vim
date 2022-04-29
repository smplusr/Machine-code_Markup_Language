"" SOULD BE LOCATED UNDER : /usr/share/vim/vim[VERSION]/syntax/

" Vim syntax file
" Language:             mml(?) configuration file
" Previous Maintainer:  unknown
" Latest Revision:      unknown


if exists("b:current_syntax")
  finish
endif

let s:cpo_save = &cpo
set cpo&vim


syn keyword mmlTodo        contained FIXME TODO XXX NOTE
syn region  mmlComment	start=+#+ end=+#\|$+
                                \ contains=mmlTodo,@Spell

syn region mmlNodeDef	start=+@+ end=+ \|$+
syn region mmlNodeCall	start=+%+ end=+ \|$+


hi def link mmlTodo		Todo
hi def link mmlComment		String
hi def link mmlNodeDef		Comment
hi def link mmlNodeCall		Special


let b:current_syntax = "mml"

let &cpo = s:cpo_save
unlet s:cpo_save
