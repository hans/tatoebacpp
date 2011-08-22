/**
 * Tatoeba Project, free collaborative creation of multilingual corpuses project
 * Copyright (C) 2011 Allan SIMON <allan.simon@supinfo.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *
 * @category Tatoebacpp
 * @package  Controllers
 * @author   Allan SIMON <allan.simon@supinfo.com>
 * @license  Affero General Public License
 * @link     http://tatoeba.org
 */

#include "Controller.h"
#include "OfUser.h"
#include "contents/of_user.h"

#include "models/OfUser.h"

namespace controllers {
namespace webs {

OfUser::OfUser(cppcms::service &serv) : Controller(serv) {

    cppcms::url_dispatcher* disp = &dispatcher();

  	//disp->assign("/sentences-of/(.*)", &OfUser::sentences_of, this, 1);
  	disp->assign("/translate-sentences-of/(.*)", &OfUser::translate_sentences_of, this, 1);
  	disp->assign("/adopt-sentence/(\\d+)", &OfUser::adopt_sentence, this, 1);
  	disp->assign("/abandon-sentence/(\\d+)", &OfUser::abandon_sentence, this, 1);

    ofUsersModel = new models::OfUser();
}

/**
 *
 */
OfUser::~OfUser() {
    delete ofUsersModel;
}

/**
 *
 */
void OfUser::translate_sentences_of(
    std::string username
) {

    contents::of_user::TranslateSentencesOf c;
    init_content(c);

    unsigned int page = 0;
    std::string  sentencesIn;

    if (request().request_method() == "GET") {
        cppcms::http::request::form_type getData = request().get();
        cppcms::http::request::form_type::const_iterator it;
       
        GET_FIELD(sentencesIn, "in");
        GET_INT_FIELD(page, "page");
    }

    c.shc.baseUrl = "/of-user/translate-sentences-of/" + username;
    c.shc.lang = c.lang;
    c.shc.currentUserHelper = c.usersHelper;

    if (sentencesIn.empty()) {

        c.shc.sentences = ofUsersModel->sentences_of(
            username,
            page
        );
    } else {
        /*
        c.baseUrl += "?in=" sentencesIn
        c.sentences = ofUsersModel->sentences_of(
            username,
            page,
            sentencesIn
        );
        */
    }

    render("of_user_translate_sentences_of", c);
}

/**
 *
 */
void OfUser::adopt_sentence(
    std::string sentenceIdStr
) {
    CHECK_PERMISSION_OR_GO_TO_LOGIN(); 
    std::stringstream ss(sentenceIdStr);
    int sentenceId = 0;
    ss >> sentenceId;
    
    const bool success = ofUsersModel->adopt_sentence(
        sentenceId,
        get_current_user_id()
    );

    if (success) {
        // TODO say that the sentence has been correctly adopted
    } else {
        // TODO print an error message
    }

    go_to_sentence(sentenceIdStr);
}

/**
 *
 */
void OfUser::abandon_sentence(
    std::string sentenceIdStr
) {
    CHECK_PERMISSION_OR_GO_TO_LOGIN(); 
    std::stringstream ss(sentenceIdStr);
    int sentenceId = 0;
    ss >> sentenceId;
    
    // TODO replace this by something more generic for right
    // management 

    const bool isOwner = ofUsersModel->is_sentence_owner(
        sentenceId,
        get_current_user_id()
    );

    if (isOwner) {
     
        const bool success = ofUsersModel->abandon_sentence(sentenceId);
        if (!success) {
            //TODO set an error message
        }

    } else {
        //TODO set an error message
    }

    go_back_to_previous_page();
}


} // end of namespace webs
} // end of namespace controllers
