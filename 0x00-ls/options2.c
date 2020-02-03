#include "hls.h"

/**
 * setug - initialises content struct with permission info
 * @entries: pointer to entries
 * @sb: stat buffer
 */
void setug(content_t *entries, struct stat sb)
{
	struct passwd *p;
	struct group *g;

	entries->uid = sb.st_uid;
	entries->gid = sb.st_gid;
	p = getpwuid(entries->uid);
	if (p)
		entries->usr = p->pw_name;
	g = getgrgid(entries->uid);
	if (g)
		entries->grp = g->gr_name;
}
