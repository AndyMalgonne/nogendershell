#include "minishell.h"

t_tree *test_cat_makefile() {
	t_tree *tree;

	tree = malloc(sizeof(t_tree));
	tree->cmd = ft_split("cat Makefile", ' ');
	tree->io = NULL;
	tree->next = NULL;
}
// cat Makefile

t_tree *test_cat_mult_infile() {
	t_tree *tree;

	tree = malloc(sizeof(t_tree));
	tree->cmd = ft_split("cat", ' ');

	tree->io = malloc(sizeof(t_iofile));
	tree->io->type = INFILE;
	tree->io->value = "Makefile";

	tree->io->next = malloc(sizeof(t_iofile));
	tree->io->next->type = INFILE;
	tree->io->next->value = ".gitignore";
	tree->io->next->next = NULL;

	tree->io = NULL;
	tree->next = NULL;
}
// cat < Makefile < .gitignore

t_tree *test_cat_mult_outfile(){
	t_tree *tree;

	tree = malloc(sizeof(t_tree));
	tree->cmd = ft_split("cat", ' ');

	tree->io = malloc(sizeof(t_iofile));
	tree->io->type = OUTFILE_TRUNC;
	tree->io->value = "test.txt";

	tree->io->next = malloc(sizeof(t_iofile));
	tree->io->next->type = OUTFILE_APPEND;
	tree->io->next->value = "test2.txt";
	tree->io->next->next = NULL;

	tree->io = NULL;
	tree->next = NULL;
}
// cat > test >> test2


t_tree *test_ultime(){
	t_tree *tree;

	tree = malloc(sizeof(t_tree));
	tree->cmd = ft_split("cat", ' ');
	tree->next = malloc(sizeof(t_tree));
	tree->next->cmd = ft_split("cat", ' ');
	tree->next->next = NULL;

	tree->io = malloc(sizeof(t_iofile));
	tree->io->type = INFILE;
	tree->io->value = "infile1";
	tree->io->next = malloc(sizeof(t_iofile));
	tree->io->next->type = OUTFILE_APPEND;
	tree->io->next->value = "outf";
	tree->io->next->next = NULL;
	tree->io->next->next = malloc(sizeof(t_iofile));
	tree->io->next->next->type = INFILE;
	tree->io->next->next->value = "infile3";
	tree->io->next->next->next = NULL;
}
// cat < infile1 >> outf < infile3 | cat
