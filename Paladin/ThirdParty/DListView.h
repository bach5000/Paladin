/*
 * Copyright 2001-2010 DarkWyrm <bpmagic@columbus.rr.com>
 * Copyright 2014 John Scipione <jscipione@gmail.com>
 * Distributed under the terms of the MIT License.
 *
 * Authors:
 *		DarkWyrm, bpmagic@columbus.rr.com
 *		John Scipione, jscipione@gmail.com
 */
#ifndef D_LIST_VIEW_H
#define D_LIST_VIEW_H

#include <Entry.h>
#include <ListItem.h>
#include <ListView.h>
#include <MenuItem.h>
#include <PopUpMenu.h>
#include <ScrollView.h>


enum
{
	REFITEM_FULL = 0,
	REFITEM_NAME,
	REFITEM_OTHER
};


class RefListItem : public BStringItem {
public:
						RefListItem(entry_ref ref,
									int32 mode = REFITEM_FULL,
									uint32 level = 0,
									bool expanded = true);
	virtual				~RefListItem(void);
					
			entry_ref	GetRef(void) const;
	virtual	void		SetRef(entry_ref ref);
	
			int32		GetDisplayMode(void) const;
	virtual	void		SetDisplayMode(int32 mode);
	
private:
		entry_ref	fItemRef;
		bool		fItemMode;
};


class DListView : public BListView {
public:
							DListView(BRect frame, const char* name,
									list_view_type type = B_SINGLE_SELECTION_LIST,
									int32 resizingMode = B_FOLLOW_LEFT | B_FOLLOW_TOP,
									int32 flags = B_WILL_DRAW | B_FRAME_EVENTS
										| B_NAVIGABLE);
							DListView(const char* name,
									list_view_type type = B_SINGLE_SELECTION_LIST,
									int32 flags = B_WILL_DRAW | B_FRAME_EVENTS
										| B_NAVIGABLE);
							~DListView(void);

	virtual	void			MouseDown(BPoint pt);
	virtual	void			MessageReceived(BMessage *message);
			
			BScrollView*	MakeScrollView(const char *name, bool horizontal,
								bool vertical);
			
			void			SetContextMenu(BPopUpMenu *menu);
			BPopUpMenu*		ContextMenu(void) const;
	virtual	void			ShowContextMenu(BPoint viewpt);

	virtual	void			SetAcceptDrops(bool value);
			bool			AcceptsDrops(void) const;
	virtual	void			RefDropped(entry_ref ref);
	virtual	void			SetDropMessage(BMessage *message);
			BMessage		DropMessage(const BMessage &message);

	virtual	int32			AddItemSorted(BStringItem *item);
	virtual	BStringItem*	FindItem(const char *text, bool matchcase = false,
								int32 offset = 0);

private:
			BPopUpMenu*		fPopUp;
			bool			fAcceptDrops;
			BMessage*		fDropMessage;
};


class RefListView : public DListView {
public:
						RefListView(BRect frame, const char* name,
								list_view_type type = B_SINGLE_SELECTION_LIST,
								uint32 resizingMask = B_FOLLOW_LEFT | B_FOLLOW_TOP,
								uint32 flags = B_WILL_DRAW | B_FRAME_EVENTS
									| B_NAVIGABLE);
						RefListView(const char* name,
								list_view_type type = B_SINGLE_SELECTION_LIST,
								uint32 flags = B_WILL_DRAW | B_FRAME_EVENTS
									| B_NAVIGABLE);
	virtual				~RefListView(void);

	virtual	void		MessageReceived(BMessage *message);
	
			int32		GetDefaultDisplayMode(void) const;
	virtual	void		SetDefaultDisplayMode(int32 mode);
	
	virtual	void		RefDropped(entry_ref ref);

	virtual	bool		AddItem(BListItem *item);
	virtual bool		AddItem(BListItem *item, int32 atIndex);

private:
		int32			fDefaultDisplayMode;
};


#endif	// D_LIST_VIEW_H
