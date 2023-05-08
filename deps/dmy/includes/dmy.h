/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dmy.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaretel- <yaretel-@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 21:32:40 by yaretel-          #+#    #+#             */
/*   Updated: 2023/05/08 10:01:16 by yaretel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// This is a custom library for easier Dynamic MemorY management

// How to use:
// Embed the entire repository in your project
// Compile the library, for example by calling the make in the repository root
// Example, inside your project's Makefile:
// ```Makefile
// 		$(dmy_root_folder)/libdmy.a: 
// 			$(MAKE) -C $(dmy_root_folder)
// ```

// This project uses the external functions:
// malloc(), free(), write()

#ifndef DMY_H
# define DMY_H
# define MALLOC 0
# define FREEONE 1
# define FREEALL 2
# include <stdlib.h>
# include <unistd.h>

// set the next macro to 1 if you want a message every time you
// double free, otherwise set to 0
# define DFREEPROC 0

typedef struct s_dmy
{
	void			*mem;
	struct s_dmy	*next;
}				t_dmy;

void	*dmy_action_malloc(t_dmy **lst, size_t size);
void	dmy_action_free(t_dmy **lst, void *ptr);
void	dmy_action_freeall(t_dmy *lst);
void	*dmy_switch(int action, size_t size, void *ptr);
void	*dmy_malloc(size_t size);
void	dmy_free(void *ptr);
void	dmy_freeall(void);
t_dmy	*dmy_lst_add(t_dmy **lst, void *mem);
int		dmy_lst_remove(t_dmy **lst, void *remove);
void	dmy_lst_free(t_dmy *lst);
t_dmy	*dmy_lstlast(t_dmy *lst);
t_dmy	*dmy_lst_findprev(t_dmy *lst, void *find);
int		dmy_lst_delnext(t_dmy **lst, t_dmy *prev);

#endif
