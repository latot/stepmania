#ifndef STEPS_H
#define STEPS_H
/*
-----------------------------------------------------------------------------
 Class: Steps

 Desc: Holds note information for a Song.  A Song may have one or more Notess.
	A Steps can be played by one or more Styles.  See StyleDef.h for more info on
	Styles.

 Copyright (c) 2001-2002 by the person(s) listed below.  All rights reserved.
	Chris Danford
-----------------------------------------------------------------------------
*/

#include "GameConstantsAndTypes.h"
#include "PlayerNumber.h"
#include "Grade.h"
class NoteData;

class Steps
{
public:
	Steps();
	~Steps();

	// initializers
	void AutogenFrom( Steps *parent, StepsType ntTo );
	void CopyFrom( Steps* pSource, StepsType ntTo );
	void CreateBlank( StepsType ntTo );

	void Compress() const;
	void Decompress() const;
	void DeAutogen();	/* If this Steps is autogenerated, make it a real Steps. */

	CString GetDescription() const { return Real()->m_sDescription; }
	Difficulty GetDifficulty() const { return Real()->m_Difficulty; }
	int GetMeter() const { return Real()->m_iMeter; }
	const float *GetRadarValues() const { return Real()->m_fRadarValues; }

	void SetDescription(CString desc);
	void SetDifficulty(Difficulty d);
	void SetMeter(int meter);
	void SetRadarValue(int r, float val);
	bool IsAutogen() const;	// Was created by autogen?


	StepsType		m_StepsType;

	void			GetNoteData( NoteData* pNoteDataOut ) const;
	void			SetNoteData( const NoteData* pNewNoteData );
	void			SetSMNoteData( const CString &out );
	CString 		GetSMNoteData() const;


	// High scores
	struct MemCardScore
	{
		int iNumTimesPlayed;
		Grade grade;
		float fScore;
		bool HigherScore( float fScore, Grade grade ) const;
	} m_MemCardScores[NUM_MEMORY_CARDS];

	void AddScore( PlayerNumber pn, Grade grade, float fScore, bool& bNewRecordOut );


	void TidyUpData();

protected:
	/* If this Steps is autogenerated, this will point to the autogen
	 * source.  If this is true, notes_comp will always be NULL. */
	const Steps *parent;

	/* We can have one or both of these; if we have both, they're always identical.
	 * Call Compress() to force us to only have notes_comp; otherwise, creation of 
	 * these is transparent. */
	mutable NoteData *notes;
	mutable CString *notes_comp;

	const Steps *Real() const;

	/* These values are pulled from the autogen source first, if there is one. */
	CString			m_sDescription;		// This text is displayed next to the number of feet when a song is selected
	Difficulty		m_Difficulty;		// difficulty classification
	int				m_iMeter;			// difficulty rating from 1-10
	float			m_fRadarValues[NUM_RADAR_CATEGORIES];	// between 0.0-1.2 starting from 12-o'clock rotating clockwise

};

bool CompareNotesPointersByRadarValues(const Steps* pNotes1, const Steps* pNotes2);
bool CompareNotesPointersByMeter(const Steps *pNotes1, const Steps* pNotes2);
bool CompareNotesPointersByDifficulty(const Steps *pNotes1, const Steps *pNotes2);
void SortNotesArrayByDifficulty( vector<Steps*> &arrayNotess );

#endif
