# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    samvalidmaps.sh                                    :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ssacrist <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/07/06 06:44:53 by dkrecisz          #+#    #+#              #
#    Updated: 2020/11/19 12:30:00 by ssacrist         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#!/bin/bash


# #ITERATE THROUGH VALID MAPS
for file in ./cub3d_destroyer/valid_maps/*.cub
do
	./cub3D $file
done

exit 0
