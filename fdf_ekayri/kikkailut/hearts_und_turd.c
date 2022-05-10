#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <mlx.h>
#include <unistd.h>
#include <math.h>
#include "libft/libft.h"

typedef struct	s_mouse_click
{
	void		*mlx_ptr;
	void		*mlx_win;
}				t_mouse_click;

typedef struct s_key
{
	void		*mlx_ptr;
	void		*mlx_win;
}				t_key;

int draw_line(void *mlx_ptr, void *win, int beginX, int beginY, int endX, int endY, int color)
{
	double deltaX = endX - beginX;
	double deltaY = endY - beginY;

	int pixels = sqrt((deltaX * deltaX) + (deltaY * deltaY));

	deltaX /= pixels;
	deltaY /= pixels;

	double pixelX = beginX;
	double pixelY = beginY;
	while (pixels)
	{
		mlx_pixel_put(mlx_ptr, win, pixelX, pixelY, color);
		pixelX += deltaX;
		pixelY += deltaY;
		--pixels;
	}
	return (0);
}

int	put_boat(int button, int x, int y, void *param)
{
	t_mouse_click	*mouse_click;

	mouse_click = param;
	if (mouse_click != NULL)
	{
		if (button == 1 && (x < 145 && y < 35))
		{
			draw_line(mouse_click->mlx_ptr, mouse_click->mlx_win, x * 2, y * 2, x * 2 + 20, y * 2, 0xFFFFFF);
			draw_line(mouse_click->mlx_ptr, mouse_click->mlx_win, 200, 200, 250, 250, 0xFFFFFF);
			draw_line(mouse_click->mlx_ptr, mouse_click->mlx_win, 200, 200, 150, 250, 0xFFFFFF);
			draw_line(mouse_click->mlx_ptr, mouse_click->mlx_win, 150, 250, 150, 350, 0xFFFFFF);
			draw_line(mouse_click->mlx_ptr, mouse_click->mlx_win, 250, 250, 250, 350, 0xFFFFFF);
			draw_line(mouse_click->mlx_ptr, mouse_click->mlx_win, 250, 350, 200, 400, 0xFFFFFF);
			draw_line(mouse_click->mlx_ptr, mouse_click->mlx_win, 150, 350, 200, 400, 0xFFFFFF);
			draw_line(mouse_click->mlx_ptr, mouse_click->mlx_win, 200, 275, 200, 325, 0xFFFFFF);
			draw_line(mouse_click->mlx_ptr, mouse_click->mlx_win, 200, 175, 200, 150, 0xFFFFFF);
			draw_line(mouse_click->mlx_ptr, mouse_click->mlx_win, 200, 425, 200, 450, 0xFFFFFF);
			draw_line(mouse_click->mlx_ptr, mouse_click->mlx_win, 265, 235, 275, 225, 0xFFFFFF);
			draw_line(mouse_click->mlx_ptr, mouse_click->mlx_win, 135, 235, 115, 225, 0xFFFFFF);
			draw_line(mouse_click->mlx_ptr, mouse_click->mlx_win, 125, 300, 100, 300, 0xFFFFFF);
			draw_line(mouse_click->mlx_ptr, mouse_click->mlx_win, 275, 300, 300, 300, 0xFFFFFF);
			draw_line(mouse_click->mlx_ptr, mouse_click->mlx_win, 135, 365, 120, 375, 0xFFFFFF);
			draw_line(mouse_click->mlx_ptr, mouse_click->mlx_win, 265, 365, 280, 375, 0xFFFFFF);
		}
		if (button == 3)
			mlx_clear_window(mouse_click->mlx_ptr, mouse_click->mlx_win);
	}
	return (1);
}

int	put_heart(int button, int x, int y, void *param)
{
	t_mouse_click	*mouse_click;

	mouse_click = param;
	printf("%d\n", button);
	printf("%d, %d\n", x, y);

	if (button == 1 && (x < 145 && y < 35))
		put_boat(button, x, y, mouse_click);
	if (mouse_click != NULL)
	{
		if (button == 1)
		{
			mlx_pixel_put(mouse_click->mlx_ptr, mouse_click->mlx_win, x, y, 0xcd5c5c);
			mlx_pixel_put(mouse_click->mlx_ptr, mouse_click->mlx_win, x - 1, y + 1, 0xcd5c5c);
			mlx_pixel_put(mouse_click->mlx_ptr, mouse_click->mlx_win, x - 2, y + 2, 0xcd5c5c);
			mlx_pixel_put(mouse_click->mlx_ptr, mouse_click->mlx_win, x - 2, y + 3, 0xcd5c5c);
			mlx_pixel_put(mouse_click->mlx_ptr, mouse_click->mlx_win, x - 1, y + 4, 0xcd5c5c);
			mlx_pixel_put(mouse_click->mlx_ptr, mouse_click->mlx_win, x, y + 5, 0xcd5c5c);
			mlx_pixel_put(mouse_click->mlx_ptr, mouse_click->mlx_win, x + 1, y + 6, 0xcd5c5c);
			mlx_pixel_put(mouse_click->mlx_ptr, mouse_click->mlx_win, x + 2, y + 7, 0xcd5c5c);
			mlx_pixel_put(mouse_click->mlx_ptr, mouse_click->mlx_win, x + 1, y + 1, 0xcd5c5c);
			mlx_pixel_put(mouse_click->mlx_ptr, mouse_click->mlx_win, x + 2, y + 2, 0xcd5c5c);
			mlx_pixel_put(mouse_click->mlx_ptr, mouse_click->mlx_win, x + 3, y + 1, 0xcd5c5c);
			mlx_pixel_put(mouse_click->mlx_ptr, mouse_click->mlx_win, x + 4, y, 0xcd5c5c);
			mlx_pixel_put(mouse_click->mlx_ptr, mouse_click->mlx_win, x + 5, y + 1, 0xcd5c5c);
			mlx_pixel_put(mouse_click->mlx_ptr, mouse_click->mlx_win, x + 6, y + 2, 0xcd5c5c);
			mlx_pixel_put(mouse_click->mlx_ptr, mouse_click->mlx_win, x + 6, y + 3, 0xcd5c5c);
			mlx_pixel_put(mouse_click->mlx_ptr, mouse_click->mlx_win, x + 5, y + 4, 0xcd5c5c);
			mlx_pixel_put(mouse_click->mlx_ptr, mouse_click->mlx_win, x + 4, y + 5, 0xcd5c5c);
			mlx_pixel_put(mouse_click->mlx_ptr, mouse_click->mlx_win, x + 3, y + 6, 0xcd5c5c);
			mlx_pixel_put(mouse_click->mlx_ptr, mouse_click->mlx_win, x, y, 0xcd5c5c);
			//mlx_string_put(mouse_click->mlx_ptr, mouse_click->mlx_win, x - 2, y - 7, 0xcd5c5c, "Syrän");
		}
		if (button == 3)
		{
			mlx_pixel_put(mouse_click->mlx_ptr, mouse_click->mlx_win, x, y, 0x8b4513);
			mlx_pixel_put(mouse_click->mlx_ptr, mouse_click->mlx_win, x - 1, y + 1, 0x8b4513);
			mlx_pixel_put(mouse_click->mlx_ptr, mouse_click->mlx_win, x + 1, y + 1, 0x8b4513);
			mlx_pixel_put(mouse_click->mlx_ptr, mouse_click->mlx_win, x, y + 2, 0x8b4513);
			mlx_pixel_put(mouse_click->mlx_ptr, mouse_click->mlx_win, x + 2, y + 2, 0x8b4513);
			mlx_pixel_put(mouse_click->mlx_ptr, mouse_click->mlx_win, x - 2, y + 2, 0x8b4513);
			mlx_pixel_put(mouse_click->mlx_ptr, mouse_click->mlx_win, x - 3, y + 3, 0x8b4513);
			mlx_pixel_put(mouse_click->mlx_ptr, mouse_click->mlx_win, x - 4, y + 3, 0x8b4513);
			mlx_pixel_put(mouse_click->mlx_ptr, mouse_click->mlx_win, x - 2, y + 3, 0x8b4513);
			mlx_pixel_put(mouse_click->mlx_ptr, mouse_click->mlx_win, x - 1, y + 3, 0x8b4513);
			mlx_pixel_put(mouse_click->mlx_ptr, mouse_click->mlx_win, x, y + 3, 0x8b4513);
			mlx_pixel_put(mouse_click->mlx_ptr, mouse_click->mlx_win, x + 1, y + 3, 0x8b4513);
			mlx_pixel_put(mouse_click->mlx_ptr, mouse_click->mlx_win, x + 2, y + 3, 0x8b4513);
			mlx_pixel_put(mouse_click->mlx_ptr, mouse_click->mlx_win, x + 3, y + 3, 0x8b4513);
			//mlx_string_put(mouse_click->mlx_ptr, mouse_click->mlx_win, x - 2, y - 7, 0x8b4513, "Pökäle");
		}
	}
	return (1);
}

/*int	mouse_event(int button, int x, int y, void *param)
{
	t_mouse_click	*mouse_click;

	printf("%d\n", button);
	printf("%d, %d\n", x, y);
	
	mouse_click = param;
	mlx_pixel_put(mouse_click->mlx_ptr, mouse_click->mlx_win, x, y, 0xFFFFFF);
	return (1);
}*/

int	put_exit(int key, int x, int y, void *param)
{
	t_key	*key_press;

	key_press = param;

	printf("%d\n", key);
	printf("%d, %d\n", x, y);

	printf("%d\n", key);
	if (key == 65307)
	{
		//mlx_destroy_window(key_press->mlx_ptr, key_press->mlx_win);
		exit(EXIT_SUCCESS);
	}
	return (1);
}

int	main(void)
{
	void	*mlx_ptr;
	void	*mlx_win;
	//void	*mlx_win2;

	mlx_ptr = mlx_init();
	mlx_win = mlx_new_window(mlx_ptr, 900, 560, "Hearts and turds 2");
	//mlx_win2 = mlx_new_window(mlx_ptr, 100, 100, "Press here to put boat");
	//mlx_string_put(mlx_ptr, mlx_win2, 20, 20, 0xFFFFFF, "Press to boat");
	t_mouse_click mouse_click;
	mouse_click.mlx_ptr = mlx_ptr;
	mouse_click.mlx_win = mlx_win;
	//mlx_mouse_hook(mlx_win, &mouse_event, &mouse_click);
	mlx_mouse_hook(mlx_win, &put_heart, &mouse_click);
	//mlx_mouse_hook(mlx_win, &put_boat, &mouse_click);

	t_key	key_press;
	key_press.mlx_ptr = mlx_ptr;
	key_press.mlx_win = mlx_win;
	mlx_key_hook(mlx_win, &put_exit, &key_press);
	mlx_string_put(mlx_ptr, mlx_win, 25, 525, 0xFFFFFF, "Press 'ESC' to exit");

	int		pixel_bits;
	int		line_bytes;
	int		endian;
	int		pixel;
	int		color;
	void	*mlx_img;
	int		x;
	int		y;
	char	*buf;

	mlx_img = NULL;
	mlx_img = mlx_new_image(mlx_ptr, 150, 35);

	buf = mlx_get_data_addr(mlx_img, &pixel_bits, &line_bytes, &endian);
	color = 0xABCDEF;

	for(int y = 0; y < 360; ++y)
	for(int x = 0; x < 640; ++x)
	{
		pixel = (y * line_bytes) + (x * 4);

		if (endian == 1)
		{
			buf[pixel + 0] = (color >> 24);
			buf[pixel + 1] = (color >> 16) & 0xFF;
			buf[pixel + 2] = (color >> 8) & 0xFF;
			buf[pixel + 3] = (color) & 0xFF;
		}
		if (endian == 0)
		{
			buf[pixel + 0] = (color) & 0xFF;
			buf[pixel + 1] = (color >> 8) & 0xFF;
			buf[pixel + 2] = (color >> 16) & 0xFF;
			buf[pixel + 3] = (color >> 24);
		}
	}
	mlx_put_image_to_window(mlx_ptr, mlx_win, mlx_img, 0, 0);
	mlx_string_put(mlx_ptr, mlx_win, 20, 15, 0x8b1a1a, "Press here to boat");
	mlx_loop(mlx_ptr);
}
