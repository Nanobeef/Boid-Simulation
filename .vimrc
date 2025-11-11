set autoread

let working_path = getcwd()
let vimrc_path = expand('<sfile>:p:h')



map <C-A> :execute "!clear && cd " . shellescape(vimrc_path) . " && (time -p ./compile.sh)" <CR>
map <C-F> :execute "!clear && cd " . shellescape(vimrc_path) . " && (time -p ./compile.sh release)" <CR>

map <C-F10> :execute "!clear && cd " . shellescape(vimrc_path) . " && (./compile.sh clean) && (time -p ./compile.sh release)" <CR>
map <C-F9> :execute "!clear && cd " . shellescape(vimrc_path) . " && (./compile.sh clean) && (time -p ./compile.sh)" <CR>

map <C-S> :execute "!clear && cd " . shellescape(vimrc_path) . " &&  ./src/build/e" <CR>
map <C-D> :execute "!clear && cd " . shellescape(vimrc_path) . " &&  gdb ./src/build/e" <CR>

nnoremap <C-H> :tabprevious <CR> :redraw! <CR>
nnoremap <C-L> :tabnext     <CR> :redraw! <CR>

nnoremap <C-U> <C-W>h
nnoremap <C-I> <C-W>j
nnoremap <C-O> <C-W>k
nnoremap <C-P> <C-W>l


if &term =~ "linux"
	let &t_SI = "\<Esc>[5 q"
	let &t_EI = "\<Esc>[2 q"
endif
