/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oderkaou <oderkaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/02 16:29:55 by ikrkharb          #+#    #+#             */
/*   Updated: 2020/02/17 22:38:31 by oderkaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

t_camera	Fill_camera_data(t_block *block)
{
	t_block_list 	*list;
	t_camera 		camera;
	int				key;
	int 			i;

	list = block->list;
	i = 0;
	init_cam(&camera);
	while (i < block->n)
	{
		key = find_camera_key(list[i].key);
		if (key == EYE)
			camera.eye = char_to_vec(list[i].value);
		if (key == LOOK_AT)
			camera.look_at = char_to_vec(list[i].value);
		if (key == FOV)
			camera.fov = ft_atof(list[i].value);
		if (key == DIST)
			camera.dist = ft_atof(list[i].value);
		i++;
	}
	return (camera);
}

t_list	*Fill_light_data(t_block *block)
{
	t_block_list	*list;
	t_light			light;
	int				key;
	int				i;

	list = block->list;
	init_light(&light);
	i = 0;
	while (i < block->n)
	{
		key = find_light_key(list[i].key);
		if (key == ORIGIN)
			light.origin = char_to_vec(list[i].value);
		if (key == INTENSITY)
			light.intensity = ft_atof(list[i].value);
		i++;
	}
	return (ft_lstnew(&light, sizeof(t_light)));
}

t_list	*Fill_object_data(t_block *block)
{
	t_block_list 	*list;
	t_object		obj;
	int				key;
	int				i;

	list = block->list;
	init_obj(&obj);
	i = 0;
	while (i < block->n)
	{
		if (list[i].key)
			key = find_object_key(list[i].key);
		if (key == NAME)
			obj.name = list[i].value;
		if (key == COLOR)
			obj.color = ft_atoi(list[i].value);
		if (key == CENTER)
			obj.center = char_to_vec(list[i].value);
		if (key == RADIUS)
			obj.radius = ft_atof(list[i].value);
		if (key == KS)
			obj.ks = ft_atof(list[i].value);
		if (key == KD)
			obj.kd = ft_atof(list[i].value);
		if (key == N)
			obj.n = ft_atof(list[i].value);
		if (key == ROT)
			obj.rot = char_to_rot(list[i].value);
		if (key == TRANS)
			obj.trans = char_to_trans(list[i].value);
		i++;
	}
	debug_rot(&(obj.rot));
	debug_trans(&(obj.trans));
	return (ft_lstnew(&obj, sizeof(t_object)));
}

void	print_linked_list(t_list *list)
{
	t_light	*light;
	
	light = NULL;
	while (list)
	{
		light = list->content;
		printf("light->origin : \t%f\t%f\t%f\n", light->origin.x, light->origin.y, light->origin.z);
		printf("light->intensity: \t%f\n", light->intensity);
		list = list->next;
	}
}

int Fill(t_parser *p, t_mlx *mlx)
{
	t_block 	*block;
	t_camera	camera;
	t_list		*lights;
	t_list		*objects;
	int			key;
	int i;

	i = 0;
	
	objects = NULL;
	lights = NULL;
	while (i < p->n)
	{
		block = &(p->blocks[i]);
		key = find_block(block);
		if (key == CAMERA)
			camera = Fill_camera_data(block);
		if (key == LIGHT)
			ft_lstadd(&lights, Fill_light_data(block));
		if (key == SHAPE)
			ft_lstadd(&objects, Fill_object_data(block));
		i++;
	}
	create_actual_objs(mlx, camera, lights, objects);
	return (1);
}
