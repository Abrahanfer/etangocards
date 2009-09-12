//-*-c++-*-
/* main.h
 *
 * Copyright (C) 2009 Abrahán Fernández Nieto
 *
 * Email: <abrahanfer@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */
#ifndef MAIN_H_
#define MAIN_H_

#define UI_DIR  DATADIR G_DIR_SEPARATOR_S PACKAGE G_DIR_SEPARATOR_S "ui"

#define FILE_UI_DIALOG_PACKAGE UI_DIR G_DIR_SEPARATOR_S "dialog_package.ui"
#define FILE_UI_DIALOG_NEW UI_DIR G_DIR_SEPARATOR_S "dialog_new.ui"
#define FILE_UI_DIALOG_CREATION_PACKAGE \
  UI_DIR G_DIR_SEPARATOR_S "dialog_creation_package.ui"
#define FILE_UI_DIALOG_PREFERENCES UI_DIR G_DIR_SEPARATOR_S \
  "dialog_preferences.ui"

#define ICONS_DIR DATADIR G_DIR_SEPARATOR_S PACKAGE G_DIR_SEPARATOR_S "icons"

#define ICONS_ETANGOCARDS_32 ICONS_DIR G_DIR_SEPARATOR_S "etangocards.32.png"
#define ICONS_ETANGOCARDS_48 ICONS_DIR G_DIR_SEPARATOR_S "etangocards.48.png"

#endif //MAIN_H_
