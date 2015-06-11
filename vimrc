:map <F5> : tabprevious<CR>
:map <F6> : tabnext<CR>
:map <F4> : tabnew .<CR>
:map <F2> : vsplit .<CR>
:map <F3> : split .<CR>
:map <F7>   <C-w><C-w>
:map <C-h> : vertical res -1<CR>
:map <C-l> : vertical res +1<CR>
:map <C-j> : res +1<CR>
:map <C-k> : res -1<CR>
:map yy  <C-]>                                                                                   
:map tt  <C-t>  

set ruler
set tabstop=3
set incsearch
set hlsearch

syntax on

set tags=/Users/chenfool/mnt/spark_app_2/tags

let Tlist_Ctags_Cmd='/usr/local/bin/ctags'
let Tlist_Auto_Open=1
let Tlist_Use_Right_Window=1
let Tlist_File_Fold_Auto_Close=1
let Tlist_Exit_OnlyWindow=1
