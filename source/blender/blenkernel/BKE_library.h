/*
 * ***** BEGIN GPL LICENSE BLOCK *****
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 * The Original Code is Copyright (C) 2001-2002 by NaN Holding BV.
 * All rights reserved.
 *
 * The Original Code is: all of this file.
 *
 * Contributor(s): none yet.
 *
 * ***** END GPL LICENSE BLOCK *****
 */
#ifndef __BKE_LIBRARY_H__
#define __BKE_LIBRARY_H__

/** \file BKE_library.h
 *  \ingroup bke
 *  \since March 2001
 *  \author nzc
 */
#ifdef __cplusplus
extern "C" {
#endif

#include "BLI_compiler_attrs.h"

struct BlendThumbnail;
struct ListBase;
struct ID;
struct ImBuf;
struct Main;
struct Library;
struct wmWindowManager;
struct bContext;
struct PointerRNA;
struct PropertyRNA;

void *BKE_libblock_alloc_notest(short type);
void *BKE_libblock_alloc(struct Main *bmain, short type, const char *name) ATTR_WARN_UNUSED_RESULT ATTR_NONNULL();
void  BKE_libblock_init_empty(struct ID *id);
void *BKE_libblock_copy_ex(struct Main *bmain, struct ID *id) ATTR_WARN_UNUSED_RESULT ATTR_NONNULL();
void *BKE_libblock_copy_nolib(struct ID *id, const bool do_action) ATTR_NONNULL();
void *BKE_libblock_copy(struct ID *id) ATTR_WARN_UNUSED_RESULT ATTR_NONNULL();
void  BKE_libblock_copy_data(struct ID *id, const struct ID *id_from, const bool do_action);
void  BKE_libblock_relink(struct ID *id);
void  BKE_libblock_rename(struct Main *bmain, struct ID *id, const char *name) ATTR_NONNULL();
void  BLI_libblock_ensure_unique_name(struct Main *bmain, const char *name) ATTR_NONNULL();

void  BKE_libblock_free(struct Main *bmain, void *idv) ATTR_NONNULL();
void  BKE_libblock_free_ex(struct Main *bmain, void *idv, bool do_id_user) ATTR_NONNULL();
void  BKE_libblock_free_us(struct Main *bmain, void *idv) ATTR_NONNULL();
void  BKE_libblock_free_data(struct Main *bmain, struct ID *id) ATTR_NONNULL();

struct ID *BKE_libblock_find_name_ex(struct Main *bmain, const short type, const char *name) ATTR_WARN_UNUSED_RESULT ATTR_NONNULL();
struct ID *BKE_libblock_find_name(const short type, const char *name) ATTR_WARN_UNUSED_RESULT ATTR_NONNULL();

void BKE_id_lib_local_paths(struct Main *bmain, struct Library *lib, struct ID *id);
void id_lib_extern(struct ID *id);
void BKE_library_filepath_set(struct Library *lib, const char *filepath);
void id_us_ensure_real(struct ID *id);
void id_us_plus(struct ID *id);
void id_us_min(struct ID *id);
void id_fake_user_set(struct ID *id);
void id_fake_user_clear(struct ID *id);

bool id_make_local(struct ID *id, bool test);
bool id_single_user(struct bContext *C, struct ID *id, struct PointerRNA *ptr, struct PropertyRNA *prop);
bool id_copy(struct ID *id, struct ID **newid, bool test);
bool id_unlink(struct ID *id, int test);
void id_sort_by_name(struct ListBase *lb, struct ID *id);

bool new_id(struct ListBase *lb, struct ID *id, const char *name);
void id_clear_lib_data(struct Main *bmain, struct ID *id);
void id_clear_lib_data_ex(struct Main *bmain, struct ID *id, bool id_in_mainlist);

struct ListBase *which_libbase(struct Main *mainlib, short type);

#define MAX_LIBARRAY    34
int set_listbasepointers(struct Main *main, struct ListBase *lb[MAX_LIBARRAY]);

/* Main API */
struct Main *BKE_main_new(void);
void BKE_main_free(struct Main *mainvar);

void BKE_main_lock(struct Main *bmain);
void BKE_main_unlock(struct Main *bmain);

struct BlendThumbnail *BKE_main_thumbnail_from_imbuf(struct Main *bmain, struct ImBuf *img);
struct ImBuf *BKE_main_thumbnail_to_imbuf(struct Main *bmain, struct BlendThumbnail *data);
void BKE_main_thumbnail_create(struct Main *bmain);

void BKE_main_id_tag_idcode(struct Main *mainvar, const short type, const int tag, const bool value);
void BKE_main_id_tag_listbase(struct ListBase *lb, const int tag, const bool value);
void BKE_main_id_tag_all(struct Main *mainvar, const int tag, const bool value);

void BKE_main_id_flag_listbase(ListBase *lb, const int flag, const bool value);
void BKE_main_id_flag_all(struct Main *bmain, const int flag, const bool value);

void BKE_main_id_clear_newpoins(struct Main *bmain);

void BKE_main_lib_objects_recalc_all(struct Main *bmain);

/* (MAX_ID_NAME - 2) + 3 */
void BKE_id_ui_prefix(char name[66 + 1], const struct ID *id);

void BKE_library_make_local(struct Main *bmain, struct Library *lib, bool untagged_only, bool set_fake);

typedef void (*BKE_library_free_window_manager_cb)(struct bContext *, struct wmWindowManager *);
typedef void (*BKE_library_free_notifier_reference_cb)(const void *);
typedef void (*BKE_library_free_editor_id_reference_cb)(const struct ID *);

void BKE_library_callback_free_window_manager_set(BKE_library_free_window_manager_cb func);
void BKE_library_callback_free_notifier_reference_set(BKE_library_free_notifier_reference_cb func);
void BKE_library_callback_free_editor_id_reference_set(BKE_library_free_editor_id_reference_cb func);

/* use when "" is given to new_id() */
#define ID_FALLBACK_NAME N_("Untitled")

#define IS_TAGGED(_id) ((_id) && (((ID *)_id)->tag & LIB_TAG_DOIT))

#ifdef __cplusplus
}
#endif

#endif  /* __BKE_LIBRARY_H__ */
