/*
* Copyright (c) 2015 MediaTek Inc.
* Author: PC Chen <pc.chen@mediatek.com>
*         Tiffany Lin <tiffany.lin@mediatek.com>
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License version 2 as
* published by the Free Software Foundation.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*/

#ifndef _MTK_VCODEC_UTIL_H_
#define _MTK_VCODEC_UTIL_H_

#include <linux/types.h>
#include <linux/dma-direction.h>

struct mtk_vcodec_mem {
	size_t size;
	void *va;
	dma_addr_t dma_addr;
};

extern int mtk_v4l2_dbg_level;
extern bool mtk_vcodec_dbg;

#define DEBUG 0

#if defined(DEBUG)

#define mtk_v4l2_debug(level, fmt, args...)				 \
	do {								 \
		if (mtk_v4l2_dbg_level >= level)			 \
			pr_info("[MTK_V4L2] level=%d %s(),%d: " fmt "\n",\
				level, __func__, __LINE__, ##args);	 \
	} while (0)

#define mtk_v4l2_err(fmt, args...)                \
	pr_err("[MTK_V4L2][ERROR] %s:%d: " fmt "\n", __func__, __LINE__, \
	       ##args)


#define mtk_v4l2_debug_enter()  mtk_v4l2_debug(3, "+\n")
#define mtk_v4l2_debug_leave()  mtk_v4l2_debug(3, "-\n")

#define mtk_vcodec_debug(h, fmt, args...)				\
	do {								\
		if (mtk_vcodec_dbg)					\
			pr_info("[MTK_VCODEC][%d]: %s() " fmt "\n",	\
				((struct mtk_vcodec_ctx *)h->ctx)->idx, \
				__func__, ##args);			\
	} while (0)

#define mtk_vcodec_err(h, fmt, args...)					\
	pr_err("[MTK_VCODEC][ERROR][%d]: %s() " fmt "\n",		\
	       ((struct mtk_vcodec_ctx *)h->ctx)->idx, __func__, ##args)

#define mtk_vcodec_debug_enter(h)  mtk_vcodec_debug(h, "+\n")
#define mtk_vcodec_debug_leave(h)  mtk_vcodec_debug(h, "-\n")

#else

#define mtk_v4l2_debug(level, fmt, args...)
#define mtk_v4l2_err(fmt, args...)
#define mtk_v4l2_debug_enter()
#define mtk_v4l2_debug_leave()

#define mtk_vcodec_debug(h, fmt, args...)
#define mtk_vcodec_err(h, fmt, args...)
#define mtk_vcodec_debug_enter(h)
#define mtk_vcodec_debug_leave(h)

#endif

void __iomem *mtk_vcodec_get_reg_addr(void *data, unsigned int reg_idx);
int mtk_vcodec_mem_alloc(void *data, struct mtk_vcodec_mem *mem);
void mtk_vcodec_mem_free(void *data, struct mtk_vcodec_mem *mem);
int mtk_vcodec_get_ctx_id(void *data);
struct platform_device *mtk_vcodec_get_plat_dev(void *data);
void mtk_vcodec_fmt2str(u32 fmt, char *str);
#endif /* _MTK_VCODEC_UTIL_H_ */
