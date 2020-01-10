/* -*- mode: C; c-file-style: "gnu"; indent-tabs-mode: nil; -*- */

/* Metacity utilities */

/* 
 * Copyright (C) 2001 Havoc Pennington
 * Copyright (C) 2005 Elijah Newren
 * 
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
 * 02111-1307, USA.
 */

#ifndef META_UTIL_H
#define META_UTIL_H

#include <glib.h>
#include <glib-object.h>

gboolean meta_is_verbose  (void);
void     meta_set_verbose (gboolean setting);
gboolean meta_is_debugging (void);
void     meta_set_debugging (gboolean setting);
gboolean meta_is_syncing (void);
void     meta_set_syncing (gboolean setting);
gboolean meta_get_replace_current_wm (void);
void     meta_set_replace_current_wm (gboolean setting);

void meta_debug_spew_real (const char *format,
                           ...) G_GNUC_PRINTF (1, 2);
void meta_verbose_real    (const char *format,
                           ...) G_GNUC_PRINTF (1, 2);

void meta_bug        (const char *format,
                      ...) G_GNUC_PRINTF (1, 2);
void meta_warning    (const char *format,
                      ...) G_GNUC_PRINTF (1, 2);
void meta_fatal      (const char *format,
                      ...) G_GNUC_PRINTF (1, 2);

typedef enum
{
  META_DEBUG_FOCUS           = 1 << 0,
  META_DEBUG_WORKAREA        = 1 << 1,
  META_DEBUG_STACK           = 1 << 2,
  META_DEBUG_THEMES          = 1 << 3,
  META_DEBUG_SM              = 1 << 4,
  META_DEBUG_EVENTS          = 1 << 5,
  META_DEBUG_WINDOW_STATE    = 1 << 6,
  META_DEBUG_WINDOW_OPS      = 1 << 7,
  META_DEBUG_GEOMETRY        = 1 << 8,
  META_DEBUG_PLACEMENT       = 1 << 9,
  META_DEBUG_PING            = 1 << 10,
  META_DEBUG_XINERAMA        = 1 << 11,
  META_DEBUG_KEYBINDINGS     = 1 << 12,
  META_DEBUG_SYNC            = 1 << 13,
  META_DEBUG_ERRORS          = 1 << 14,
  META_DEBUG_STARTUP         = 1 << 15,
  META_DEBUG_PREFS           = 1 << 16,
  META_DEBUG_GROUPS          = 1 << 17,
  META_DEBUG_RESIZING        = 1 << 18,
  META_DEBUG_SHAPES          = 1 << 19,
  META_DEBUG_COMPOSITOR      = 1 << 20,
  META_DEBUG_EDGE_RESISTANCE = 1 << 21
} MetaDebugTopic;

void meta_topic_real      (MetaDebugTopic topic,
                           const char    *format,
                           ...) G_GNUC_PRINTF (2, 3);

void meta_push_no_msg_prefix (void);
void meta_pop_no_msg_prefix  (void);

gint  meta_unsigned_long_equal (gconstpointer v1,
                                gconstpointer v2);
guint meta_unsigned_long_hash  (gconstpointer v);

void meta_print_backtrace (void);

const char* meta_gravity_to_string (int gravity);

#include <libintl.h>
#define _(x) dgettext (GETTEXT_PACKAGE, x)
#define N_(x) x

char* meta_g_utf8_strndup (const gchar *src, gsize n);

void  meta_free_gslist_and_elements (GSList *list_to_deep_free);

GPid meta_show_dialog (const char *type,
                       const char *title,
                       const char *message,
                       gint timeout,
                       const char *ok_text,
                       const char *cancel_text,
                       const int transient_for,
                       GSList *columns,
                       GSList *entries);

/* To disable verbose mode, we make these functions into no-ops */
#ifdef WITH_VERBOSE_MODE

#define meta_debug_spew meta_debug_spew_real
#define meta_verbose    meta_verbose_real
#define meta_topic      meta_topic_real

#else

#  ifdef G_HAVE_ISO_VARARGS
#    define meta_debug_spew(...)
#    define meta_verbose(...)
#    define meta_topic(...)
#  elif defined(G_HAVE_GNUC_VARARGS)
#    define meta_debug_spew(format...)
#    define meta_verbose(format...)
#    define meta_topic(format...)
#  else
#    error "This compiler does not support varargs macros and thus verbose mode can't be disabled meaningfully"
#  endif

#endif /* !WITH_VERBOSE_MODE */

#include <glib-object.h>

#define META_TYPE_NEXUS            (meta_nexus_get_type ())
#define META_NEXUS(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), META_TYPE_NEXUS, MetaNexus))
#define META_NEXUS_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass), META_TYPE_NEXUS, MetaNexusClass))
#define META_IS_NEXUS(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), META_TYPE_NEXUS))
#define META_IS_NEXUS_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), META_TYPE_NEXUS))
#define META_NEXUS_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj), META_TYPE_NEXUS, MetaNexusClass))

typedef struct _MetaNexus
{
  GObject parent_instance;
} MetaNexus;

typedef struct _MetaNexusClass
{
  GObjectClass parent_class;
} MetaNexusClass;

GType meta_nexus_get_type (void) G_GNUC_CONST;
MetaNexus *meta_nexus_new ();

/**
 * An object which exists purely to attach signals to; this is to receive
 * signals when a child process exits.  The signal is "sigchld" with no detail.
 */
extern MetaNexus *sigchld_nexus;

#endif /* META_UTIL_H */


