/*
 * Copyright (C) 2015  Elvis Teixeira
 *
 * This source code is free software: you can redistribute it
 * and/or modify it under the terms of the GNU Lesser General
 * Public License as published by the Free Software Foundation,
 * either version 3 of the License, or (at your option) any
 * later version.
 *
 * This source code is distributed in the hope that it will be
 * useful, but WITHOUT ANY WARRANTY; without even the implied
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 * PURPOSE.  See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General
 * Public License along with this program.
 * If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef QSL_GLOBAL_H
#define QSL_GLOBAL_H

#include <QtCore>

#if defined(QSL_BUILD)
#define QSL_API Q_DECL_EXPORT
#elif defined(QSL_LIB)
#define QSL_API Q_DECL_IMPORT
#else
#define QSL_API
#endif

#define QSL_PRIVATE_DECLS \
    class Private;        \
    Private *const m;

// #define QSL_DARK_STYLE

#endif // QSL_GLOBAL_H
