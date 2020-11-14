#include "tags.h"

bool Tags::extractAPE(TagLib::APE::Tag* tag, TagLib::ByteVector& pic) {
	const TagLib::APE::ItemListMap& listMap = tag->itemListMap();

	if (listMap.contains("COVER ART (FRONT)")) {
		const TagLib::ByteVector nullStringTerminator(1, 0);
		TagLib::ByteVector item = listMap["COVER ART (FRONT)"].value();
		const int pos = item.find(nullStringTerminator);	// Skip the filename.

		if (pos != -1) {
			pic = item.mid(pos + 1);
			return true;
		}
	}

	return false;
}

bool Tags::extractID3(TagLib::ID3v2::Tag* tag, TagLib::ByteVector& pic) {
	const TagLib::ID3v2::FrameList& frameList = tag->frameList("APIC");

	if (!frameList.isEmpty()) {
		const auto* frame = (TagLib::ID3v2::AttachedPictureFrame*)frameList.front();
		pic = frame->picture();
        return true;
	}

	return false;
}

bool Tags::extractASF(TagLib::ASF::File* file, TagLib::ByteVector& pic) {
	const TagLib::ASF::AttributeListMap& attrListMap = file->tag()->attributeListMap();

	if (attrListMap.contains("WM/Picture")) {
		const TagLib::ASF::AttributeList& attrList = attrListMap["WM/Picture"];
		if (!attrList.isEmpty()) {
			const TagLib::ASF::Picture& wmpic = attrList[0].toPicture();
			if (wmpic.isValid()) {
				pic = wmpic.picture();
                return true;
			}
		}
	}

	return false;
}

bool Tags::extractFLAC(TagLib::FLAC::File* file, TagLib::ByteVector& pic) {
	const TagLib::List<TagLib::FLAC::Picture*>& picList = file->pictureList();
	if (!picList.isEmpty()) {
		const TagLib::FLAC::Picture* image = picList[0];
		pic = image->data();
        return true;
	}

	return false;
}

bool Tags::extractMP4(TagLib::MP4::File* file, TagLib::ByteVector& pic) {
	TagLib::MP4::Tag* tag = file->tag();
	const TagLib::MP4::ItemListMap& itemListMap = tag->itemListMap();
	if (itemListMap.contains("covr")) {
		const TagLib::MP4::CoverArtList& coverArtList = itemListMap["covr"].toCoverArtList();
		if (!coverArtList.isEmpty()) {
			const TagLib::MP4::CoverArt* image = &(coverArtList.front());
			pic = image->data();
            return true;
		}
	}

	return false;
}

/*
** Attempts to extract cover art from audio files.
**
*/
void Tags::extractAlbumCover(const TagLib::FileRef& fr) {
	TagLib::ByteVector pic;
    bool found = false;

    album_cover = nullptr;

    if (fr.isNull()) {
        album_cover = new QPixmap(":no_cover.jpg");
        return;
    }

	if (TagLib::MPEG::File *file = dynamic_cast<TagLib::MPEG::File *>(fr.file())) {
		if (file->ID3v2Tag()) {
			found = extractID3(file->ID3v2Tag(), pic);
		}
		if (!found && file->APETag()) {
			found = extractAPE(file->APETag(), pic);
		}
	}
	else if (TagLib::FLAC::File *file = dynamic_cast<TagLib::FLAC::File *>(fr.file())) {
		found = extractFLAC(file, pic);

		if (!found && file->ID3v2Tag()) {
			found = extractID3(file->ID3v2Tag(), pic);
		}
	}
	else if (TagLib::MP4::File *file = dynamic_cast<TagLib::MP4::File *>(fr.file())) {
		found = extractMP4(file, pic);
	}
	else if (TagLib::ASF::File *file = dynamic_cast<TagLib::ASF::File *>(fr.file())) {
		found = extractASF(file, pic);
	}
	else if (TagLib::APE::File *file = dynamic_cast<TagLib::APE::File *>(fr.file())) {
		if (file->APETag()) {
			found = extractAPE(file->APETag(), pic);
		}
	}
	else if (TagLib::MPC::File *file = dynamic_cast<TagLib::MPC::File *>(fr.file())) {
		if (file->APETag()) {
			found = extractAPE(file->APETag(), pic);
		}
	}

	if (found) {
        QImage image;
        image.loadFromData((const uchar *)pic.data(), pic.size());
        album_cover = new QPixmap(QPixmap::fromImage(image));
    }

    if (!album_cover || album_cover->isNull()) {
        album_cover = new QPixmap(":no_cover.jpg");
    }
}
