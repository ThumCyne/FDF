#include "fdf.h"

int	ft_abs(int a)
{
	if (a < 0)
		return (-a);
	return (a);
}

int	ft_max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

int	ft_wdcounter(char const *str, char c)
{
	int	words;
	int	i;

	i = 0;
	words = 0;
	while (str[i])
	{
		while (str[i] == c && str[i] != '\0')
			i++;
		if (str[i])
			words++;
		while (str[i] != c && str[i] != '\0')
			i++;
	}
	return (words);
}

static char	**memory_giver(char const *str, char c)
{
	char	**res;
	int		letters;
	int		i;
	int		j;

	res = (char **)malloc(sizeof(char *) * (ft_wdcounter(str, c) + 1));
	i = 0;
	j = 0;
	while (str[i])
	{
		letters = 0;
		while (str[i] == c && str[i])
			i++;
		while (str[i] != c && str[i] != '\0')
		{
			letters++;
			i++;
		}
		if (letters > 0)
			res[j++] = (char *)malloc(sizeof(char) * letters + 1);
	}
	res[j] = 0;
	return (res);
}

char	**ft_split(char const *str, char c)
{
	char	**res;
	int		i;
	int		j;
	int		str_number;
	int		size;

	if (str == NULL)
		return (NULL);
	size = ft_wdcounter(str, c);
	res = memory_giver(str, c);
	if (res == NULL)
		return (NULL);
	i = 0;
	str_number = 0;
	while (str_number < size)
	{
		while (str[i] == c && str[i])
			i++;
		j = 0;
		while (str[i] != c && str[i])
			res[str_number][j++] = str[i++];
		res[str_number][j] = '\0';
		str_number++;
	}
	return (res);
}






char	*ft_strjoin(char *s, char c)
{
	int		i;
	char	*str;

	i = 0;
	while (s[i])
		i++;
	str = (char *)malloc(i + 2);
	if (!str)
		return (0);
	i = 0;
	while (s[i])
	{
		str[i] = s[i];
		i++;
	}
	str[i] = c;
	str[i + 1] = '\0';
	return (str);
}

int	get_next_line(int fd, char **line)
{
	int		flag;
	char	buffer;
	char	*tmp;

	*line = (char *)malloc(1);
	if (!line)
		return (-1);
	*line[0] = '\0';
	flag = 1;
	while (flag > 0)
	{
		flag = read(fd, &buffer, 1);
		if (buffer == '\n')
			break ;
		tmp = ft_strjoin(*line, buffer);
		free(*line);
		*line = tmp;
	}
	return (flag);
}

////draw
    // iterate on height , and width 
    // draw two lines on each point(x,y) : line1(x,y)(x + 1,y)    line2(x,y)(x,y + 1)
    //aplly iso metric 
    // mlx_put_pixel 





////parse
//parse function return a struct with all parsed data

//====> cout height 
//====> cout width

//===> **matrix = (** int)malloc * height
    //=> matrix[i] = (int *)malloc * width


//====> fill data : split each row 
       //=> matrix[i] = atoi(splited str's)

int     get_height(char *filename)
{
    int height;
    char *line;
    int fd;
    fd = open(filename, O_RDONLY, 0);
    height = 0;
    while (get_next_line(fd, &line))
    {
        height++;
        free(line);
    }
    free(line);
    close(fd);
    return (height);
    
}

int	get_width(char *file_name)
{
	int		width;
	int		fd;
	char	*line;

	fd = open(file_name, O_RDONLY, 0);
	width = 0;
	get_next_line(fd, &line);
	width = ft_wdcounter(line, ' ');
	free(line);
	return (width);
}

void     fill_matrice(int *matriceline, char *line)
{
    char    **coords;
    int     i;

    coords = ft_split(line, ' ');
    i = 0;
    while (coords[i])
    {
        matriceline[i] = atoi(coords[i]);
        free(coords[i++]);
    }
    free(coords);
}

t_fdf   *parse(char *filename)
{
    int   i;
    t_fdf  *fdf;
    int     fd;
    char    *line;
    
    fdf = malloc(sizeof(t_fdf));
    fdf->height = get_height(filename);
    fdf->width = get_width(filename);
    fdf->matrice = (int **)malloc(sizeof (int *) * fdf->height );
    i = 0;
    while (i <= fdf->height)
        fdf->matrice[i++] = (int *)malloc(sizeof (int) * fdf->width);
    
    fd = open(filename, O_RDONLY, 0);    
    i = 0;
    while (get_next_line(fd, &line))
    {
        fill_matrice(fdf->matrice[i++], line);
        free(line);
    }
    return (fdf);
}

void	isometric(float *x, float *y, float z)
{
	*x = (*x - *y) * cos(0.8);
	*y = (*x + *y) * sin(0.8) - z;
}
//draw line(x,y,x1,y1, fdf)
void    draw_line(float x,float y,float x1,float y1, t_fdf *fdf)
{
    int z;
    int z1;
    float xstep;
    float ystep;
    int     max;
    
    z = fdf->matrice[(int)y][(int)x];
    z1 = fdf->matrice[(int)y1][(int)x1];    
    x *= SCALE;
    y *= SCALE;
    x1 *= SCALE;
    y1 *= SCALE;
    isometric(&x, &y, z);
    isometric(&x1, &y1, z1);
    xstep = x1 - x;
    ystep = y1 - y;

    max = ft_max(ft_abs(xstep), ft_abs(ystep));
    xstep /= max;
    ystep /= max;

    while ((int)(x1 - x) || (int)(y1 - y))
    {
        mlx_pixel_put(fdf->mlx, fdf->win, x + 200, y + 200, 0xffffff);
        x += xstep;
        y += ystep;
    }
}


//draw (fdf)

void    draw(t_fdf *fdf)
{
    int x;
    int y;

    y = 0;
    while (y < fdf->height)
    {
        x = 0;
        while (x < fdf->width)
        {
            if (x < fdf->width - 1)
                draw_line(x, y, x+1, y, fdf);
            if (y < fdf->height - 1)
                draw_line(x, y, x, y+1, fdf);
            x++;
        } 
        y++; 
    }
}


int     main(int ac, char **av)
{
    // int i;
    // i = 0;
    // int j;
    // j = 0;
    t_fdf  *fdf;

    (void)ac;
    fdf = parse (av[1]);
    fdf->mlx = mlx_init();
    fdf->win = mlx_new_window(fdf->mlx, 1000, 1000 , "FDF");
    
    //  for printing map
    // while (i <= fdf->height)
    // {
    //     j = 0;
    //     while (j <= fdf->width)
    //     {
    //         printf("%3d",fdf->matrice[i][j]);
    //         j++;
    //     }
    //     printf("\n");
    //     i++;
    // }

    draw(fdf);



    //handle keys
    mlx_loop(fdf->mlx);
    return 0;
}