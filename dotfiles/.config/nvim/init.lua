
vim.pack.add({
	"https://github.com/stevearc/conform.nvim",
	"https://github.com/neovim/nvim-lspconfig",
	{ src = "https://github.com/nvim-treesitter/nvim-treesitter", version = "master" },
})

-- Behaviors
vim.opt.background = 'dark'
vim.opt.backspace = { 'indent', 'eol', 'start' }
vim.opt.backup = false
vim.opt.clipboard = 'unnamedplus'
vim.opt.compatible = false
vim.opt.encoding = 'utf-8'
vim.opt.expandtab = false
vim.opt.incsearch = true
vim.opt.list = true
vim.opt.listchars = { tab = '› ', trail = '‧' }
vim.opt.mouse = 'a'
vim.opt.number = true
vim.opt.relativenumber = true
vim.opt.showmode = false
vim.opt.signcolumn = 'yes:1'
vim.opt.smartindent = true
vim.opt.smarttab = true
vim.opt.termguicolors = false

-- Keybinds
vim.g.mapleader = ' '
vim.keymap.set('n', '<Leader>SS', ':%s//g<Left><Left>')
vim.keymap.set({'v', 'x'}, '<Leader>SS', ':s//g<Left><Left>')
vim.keymap.set('n', 'XX', ':w!<CR>')

-- Statusline
function _G.ShowMode()
	local m = vim.fn.mode()
	if m == 'n' then return 'normal'
	elseif m == 'i' then return 'insert'
	elseif m == 'v' then return 'visual'
	elseif m == 'V' then return 'visual_l'
	elseif m == '\022' then return 'visual_b'
	elseif m == 'c' then return 'command'
	elseif m == 'R' then return 'replace'
	else return m
	end
end

vim.opt.statusline = table.concat({
	' %{v:lua.ShowMode()}', ' %f', ' %m', '%=', ' %y',
	' %{&fileencoding}', ' [%{&fileformat}]', ' %p%%', ' %l:%c', ' '
})

vim.cmd('colorscheme vim')
vim.cmd('syntax on')

vim.api.nvim_set_hl(0, 'Normal', { ctermbg = 'none' })
vim.api.nvim_set_hl(0, 'NormalNC', { ctermbg = 'none' })
vim.api.nvim_set_hl(0, 'EndOfBuffer', { ctermbg = 'none' })
vim.api.nvim_set_hl(0, 'MsgArea', { ctermbg = 'none' })
vim.api.nvim_set_hl(0, 'StatusLine', { bold = true })
vim.api.nvim_set_hl(0, 'Comment', { ctermfg = 'darkcyan' })
vim.api.nvim_set_hl(0, 'Constant', { bold = false, ctermfg = 'darkred' })
vim.api.nvim_set_hl(0, 'Function', {  bold = true, ctermfg = 'lightgray' })
vim.api.nvim_set_hl(0, 'Identifier', {  bold = false, ctermfg = 'none' })
vim.api.nvim_set_hl(0, 'LineNr', { bold = true, ctermfg = 'darkgray' })
vim.api.nvim_set_hl(0, 'NormalFloat', { ctermbg = 'none' })
vim.api.nvim_set_hl(0, 'PreProc', { ctermfg = 'cyan' })
vim.api.nvim_set_hl(0, 'Statement', { bold = true, ctermfg = 'darkyellow' })
vim.api.nvim_set_hl(0, 'Special', { bold = true, ctermfg = 'blue' })
vim.api.nvim_set_hl(0, 'Title', { ctermfg = 'magenta' })
vim.api.nvim_set_hl(0, 'Type', { bold = true,  ctermfg = 'green' })
vim.api.nvim_set_hl(0, '@constant.builtin', { link = 'Constant' })
vim.api.nvim_set_hl(0, '@type.builtin', { link = 'Type' })
vim.api.nvim_set_hl(0, '@property', { ctermfg = 'none' })
vim.api.nvim_set_hl(0, '@keyword.import', { link = 'PreProc' })
vim.api.nvim_set_hl(0, '@keyword.type', { link = 'Type' })
vim.api.nvim_set_hl(0, '@lsp.type.macro', { link = 'Constant' })
vim.api.nvim_set_hl(0, '@lsp.type.property', { ctermfg = 'none' })
vim.api.nvim_set_hl(0, '@lsp.type.operator', { link = 'Special' })
vim.api.nvim_set_hl(0, '@lsp.type.variable', { ctermfg = 'none' })
vim.api.nvim_set_hl(0, '@number', { link = 'Constant' })
vim.api.nvim_set_hl(0, '@operator', { link = 'Special' })
vim.api.nvim_set_hl(0, '@variable', { ctermfg = 'none' })
vim.api.nvim_set_hl(0, '@variable.parameter', { ctermfg = 'none' })
vim.api.nvim_set_hl(0, "DiagnosticSignError", { bold = true, ctermfg = 'darkred' })
vim.api.nvim_set_hl(0, "DiagnosticSignWarn",  { bold = true, ctermfg = 'darkyellow' })
vim.api.nvim_set_hl(0, "DiagnosticSignInfo",  { bold = true, ctermfg = 'blue' })
vim.api.nvim_set_hl(0, "DiagnosticSignHint",  { bold = true, ctermfg = 'green' })
vim.api.nvim_set_hl(0, "SignColumn", { ctermbg = "none" })


-- <plugins> conform
require('conform').setup({
	formatters_by_ft = { c = { 'clang-format' }, cpp = { 'clang-format' }, },
	formatters = {
		['clang-format'] = {
			cmd = 'clang-format',
			args = {
				"--style=file:"
				..
				vim.fn.expand("~/.config/clang-format/freebsd-knr")
			}
		},
	},
	format_on_save = { lsp_fallback = true, timeout_ms = 1000, },
})

-- <plugins> nvim-treesitter
require 'nvim-treesitter.configs'.setup { highlight = { enable = true } }

vim.lsp.enable('clangd')
vim.lsp.enable('zls')
vim.lsp.enable('superhtml')
vim.lsp.enable('markdown_oxide')

vim.api.nvim_create_autocmd('LspAttach', {
	callback = function(ev)
		local opts = { buffer = ev.buf }
		vim.keymap.set('n', 'gd', vim.lsp.buf.definition, opts)
		vim.keymap.set('n', 'gr', vim.lsp.buf.references, opts)
		vim.keymap.set('n', 'K', vim.lsp.buf.hover, opts)
	end
})
