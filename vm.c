/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   vm.c											   :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: tbailleu <tbailleu@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2020/01/26 17:24:21 by tbailleu		  #+#	#+#			 */
/*   Updated: 2020/02/03 07:39:22 by tbailleu		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <math.h>
#include <time.h>

in_addr_t	get_my_ip(char *buf)
{
	FILE		*fp;

	fp = popen("hostname -s | sed -E  'y|erp|1..|;s|^|10.|;s|$|        |'", "r");
	fread(buf, 1, 15, fp);
	buf[17] = 0;
	fclose(fp);
	return (inet_addr(buf));
}

typedef struct	s_res
{
	int 			recv_ok;
	int 			send_ok;
	in_addr_t		my_ip;
	in_addr_t		ip_p2;
	int				fd_client;
	int				fd_serveur;
	in_port_t	my_port;
	in_port_t	port_p2;
}				t_res;

void	die_with_error(char *err, t_res *s)
{
	puts(err);
	exit(1);
	//propre
	(void)s;
}

int		get_tcp_socket(struct sockaddr_in *s_addr, in_addr_t ip, in_port_t port)
{
	int					sock;

	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		return (-1);
	memset(s_addr, 0, sizeof(*s_addr));
	s_addr->sin_family = AF_INET;
	s_addr->sin_addr.s_addr = ip;
	s_addr->sin_port = htons(port);
	printf("start: %X:%d\n", ip, port);

	if (bind(sock, (struct sockaddr *)s_addr, sizeof(*s_addr)) < 0)
		return (-2);
	return (sock);
}

int		get_udp_socket(struct sockaddr_in *s_addr, in_port_t port, int serv)
{
	int					sock;
	int					perm;

	if ((sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
		return (-1);
	memset(s_addr, 0, sizeof(*s_addr));
	s_addr->sin_family = AF_INET;
	s_addr->sin_addr.s_addr = serv ? 0 : -1u;
	s_addr->sin_port = htons(port);
	perm = 1;
	if (setsockopt(sock, SOL_SOCKET, SO_BROADCAST, &perm, sizeof(perm)) < 0)
		return (-2);
	if (serv && bind(sock, (struct sockaddr *)s_addr, sizeof(*s_addr)) < 0)
		return (-3);
	return (sock);
}

void	*disc_recv(t_res *s)
{
	struct sockaddr_in	s_addr_udp;
	struct sockaddr_in	s_addr_tcp;
	int					sock_udp;
	int					sock_tcp;
	char				buff[25];

	if ((sock_udp = get_udp_socket(&s_addr_udp, 4242, 1)) < 0)
		die_with_error("Il y a deja un serveur en route recv", s);
	while (!s->recv_ok)
		if ((recv(sock_udp, buff, 24, 0) == 24))
		{
			buff[18] = 0;
			s->port_p2 = atoi(&buff[19]);
			s->ip_p2 = inet_addr(&buff[3]);
			if (s->ip_p2 != s->my_ip && s->port_p2 != s->my_port &&
				s->ip_p2 != -1u && 10000 <= s->port_p2 && s->port_p2 < 32000)
			{
				printf("%X:%d\n",s->ip_p2, s->port_p2);
				if ((s->fd_serveur = socket(AF_INET, SOCK_STREAM, 0)) < 0)
					die_with_error("get_tcp_socket(): erreur bizzard 1", s);
				memset(&s_addr_tcp, 0, sizeof(s_addr_tcp));
				s_addr_tcp.sin_family = AF_INET;
				s_addr_tcp.sin_addr.s_addr = s->ip_p2;
				s_addr_tcp.sin_port = htons(s->port_p2);
				if (!connect(s->fd_serveur, (struct sockaddr *)
					&s_addr_tcp, sizeof(s_addr_tcp)))
					s->recv_ok = 1;
			}
		}
	return ((close(sock_udp) ? NULL : NULL));
}

char	*ft_itoa(int n)
{
	char	*s;
	char	tmp;
	int	len;

	len = 0;
	if ((s = (char*)malloc(12)) == NULL)
		return (NULL);
	while (n >= 10)
	{
		s[len] = n % 10 + '0';
		len++;
		n /= 10;
	}
	s[len] = n + '0';
	s[len+1] = 0;
	n = 0;
	while (n < len / 2)
	{
		tmp = s[len - n];
		s[len - n] = s[n];
		s[n] = tmp;
		n++;
	}
	return (s);
}

void	*disc_send(t_res *s)
{
	struct sockaddr_in	s_addr;
	int					sock;
	char				buff[25];

	memcpy(buff, "tba               :", 19);
	get_my_ip(&buff[3]);
	memcpy(&buff[19], ft_itoa(s->my_port), 5);
	if ((sock = get_udp_socket(&s_addr, 4242, 0)) < 0)
		die_with_error("get_udp_socket(): erreur bizzard", s);
	while (!s->send_ok)
	{
		printf("%s\n", buff);
		if (sendto(sock, buff, 24, 0, (struct sockaddr *)
			&s_addr, sizeof(s_addr)) != 24)
			die_with_error("sendto(): probleme d'envoi", s);
		if (!s->send_ok)
			sleep(3);
	}
	close(sock);
	return (NULL);
}

int		start_local_serv(t_res *s)
{
	int					sock;
	unsigned int		len;
	struct sockaddr_in	s_addr;
	struct sockaddr_in	client;


	if ((sock = get_tcp_socket(&s_addr, s->my_ip, s->my_port)) < 0)
		return (-1);
	if (listen(sock, 1) < 0)
		return (-2);
	while ((s->fd_client = accept(sock, (struct sockaddr*)&client, &len)) < 0)
	{
		puts("wait accept");
		sleep(1);
	}
	s->send_ok = 1;
	while (!s->recv_ok)
	{
		puts("wait recv_ok");
		sleep(1);
	}
	return (sock);
}

void	*show_msg(t_res *s)
{
	char	buf[50];
	while (1)
	{
		memset(buf, 0, 50);
		write(1, buf, read(s->fd_serveur, buf, 50));
	}

}

int		main(void)
{
	pthread_t	thread[2];
	t_res		s;
	int			serv_sock;
	char		buf[50];

	srand(clock());
	s.send_ok = 0;
	s.recv_ok = 0;
	s.my_ip = get_my_ip(buf);;
	s.my_port = 10000 + rand() % 22000;
	printf("localport: %d\n", s.my_port);

	if (pthread_create(&thread[0], NULL, (void *(*)(void *))&disc_recv, &s))
		die_with_error("pthread_create(0): failed", &s);
	if (pthread_create(&thread[1], NULL, (void *(*)(void *))&disc_send, &s))
		die_with_error("pthread_create(1): failed", &s);

	if ((serv_sock = start_local_serv(&s)) < 0)
		die_with_error("start_local_serv(): failed", &s);

	puts("connection activated");

	if (pthread_create(&thread[1], NULL, (void *(*)(void *))&show_msg, &s))
		die_with_error("pthread_create(1): failed", &s);

	while (1)
	{
		memset(buf, 0, 50);
		write(s.fd_client, buf, read(0, buf, 50));
	}

	while (read(0, buf, 50));
	close(serv_sock);

}
