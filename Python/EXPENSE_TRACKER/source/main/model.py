'''
This module contain all models related to Main Menu app.
'''
import settings
import os


class MainMenuModel:

    '''
    This model will initialize the database.
    '''

    def init_db(self) -> None:
        '''
        THis function will create new database if it doesn't exict yet
        '''

        if not os.path.exists(settings.DATABASE_PATH):
            db_file = open(settings.DATABASE_PATH, "w")
            db_file.close()
