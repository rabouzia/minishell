/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recap.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabouzia <rabouzia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 01:19:40 by rabouzia          #+#    #+#             */
/*   Updated: 2024/06/12 15:42:52 by rabouzia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
en entree t_ast* ast
il faut verifier le type du node present

int exec(minishell, ast)
{
    fn_tab = [exec_and, exec_or, exec_pipex, exec_cmd]
}

int exec_or(minishell, left, right) 
{
    int ret_left = exec(left);
    if (ret_left == 0)
        return (ret_left);
    return (exec(right));
}

int exec_and(minishell, left, right)
{
    int ret_left = exec(left);
    if (ret_left != 0)
        return (ret_left);
    return (exec(right));
}

int exec_pipe(minishell, left, right)
{

}

*/