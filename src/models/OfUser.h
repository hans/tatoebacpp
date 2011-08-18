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
 * @package  Models
 * @author   Allan SIMON <allan.simon@supinfo.com>
 * @license  Affero General Public License
 * @link     http://tatoeba.org
 */


#ifndef TATOEBACPP_MODELS_OF_USERS_H
#define TATOEBACPP_MODELS_OF_USERS_H

#include "models/SqliteModel.h"
#include "results/sentences.h"

namespace models {

class Sentences;

/**
 * @class OfUser
 *
 * @brief Model that contain all the actions to modify/add/get the relation
 *        between a user and the things he can Own (sentences, comments etc.)
 *
 * @since 17 August 2011
 */
class OfUser : public SqliteModel {

    public:
        /**
         * @brief Constructor
         *
         * @since 17 August 2011
         */
        OfUser(cppdb::session sqliteDb);

        OfUser();

        /**
         * @brief Destructor
         *
         * @since 17 August 2011
         */
        ~OfUser();

        /*
        bool adopt(
            const int sentenceId,
            const int userId,
            const std::string &isoCode
        );
        */

        /**
         * @brief Set the owner of a sentence
         *
         * @param sentenceId Id of the sentence to adopt
         * @param userId     Id of the owner
         *
         * @return True if the ownership is correctly set, false otherwise
         *
         * @since 17 August 2011
         */
        bool adopt_sentence(
            const int sentenceId,
            const int userId
        );
        
        /**
         * @brief Remove the ownership of a sentence
         *
         * @param sentenceId Id of the sentence to abandon
         *
         * @return True if the sentence is correctly abandonned
         * @since 17 August 2011
         */
        bool abandon_sentence(
            const int sentenceId
        );
    
        std::string get_owner_name_of_sentence(
            const int sentenceId
        );
};

} // end of namespace models

#endif
