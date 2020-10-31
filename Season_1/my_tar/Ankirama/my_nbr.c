int	my_pow(int nbr, int expo)
{
  if (expo == 0)
    return (1);
  else
    return (nbr * my_pow(nbr, expo - 1));
}

int	oct_to_int(int oct)
{
  int	nbr;
  int	i;
  int	tmp;

  nbr = 0;
  i = 0;
  while (oct != 0)
    {
      tmp = oct % 10;
      oct = oct / 10;
      nbr = nbr + tmp * my_pow(8, i);
      i += 1;
    }
  return (nbr);
}