#include "hls.h"

/**
 * filterhidden - filters hidden files
 * @ep: entry pointer to check entry names
 * @opt: options struct to check if enabled
 *
 * Return: true if filtering otherwise false
 */
bool filterhidden(struct dirent *ep, option_t *opt)
{
	if (*ep->d_name == '.' && !opt->hidden && !opt->hiddenavigation)
		return (true);
	if (opt->hidden)
		return (false);
	if (opt->hiddenavigation && (_strcmp(ep->d_name, ".") == 0 || _strcmp(ep->d_name, "..") == 0))
		return (true);
	return (false);
}
