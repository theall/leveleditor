##
# areapropertycommand.py
# Copyright 2015-2016,Bilge Theall <wazcd@163.com>
#
# This file is part of 2dfight.
#
# This program is free software; you can redistribute it and/or modify it
# under the terms of the GNU General Public License as published by the Free
# Software Foundation; either version 2 of the License, or (at your option)
# any later version.
#
# This program is distributed in the hope that it will be useful, but WITHOUT
# ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
# FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
# more details.
#
# You should have received a copy of the GNU General Public License along with
# this program. If not, see <http://www.gnu.org/licenses/>.
##

from PyQt5.QtWidgets import (
    QUndoCommand
)
from PyQt5.QtCore import (
    pyqtSignal,
    QCoreApplication
)

class AreaPropertyCommand(QUndoCommand):
    X       = 1
    
    Name        = "Change Character Name"
    Sex         = "Change Character Sex"
    Icon        = "Change Character Icon"
    Age         = "Change Character Age"
    Height      = "Change Character Height"
    Weight      = "Change Character Weight"
    Force       = "Change Character Force"
    Ai          = "Change Character Ai"
    Scale       = "Change Character Scale"
    Author      = "Change Author"
    Email       = "Change Email"
    Description = "Change Character Description"

    ##
    # Constructs a command that changes the value of the given AreaPropertyCommand.
    #
    # Can only be used for the HexSideLength AreaPropertyCommand.
    #
    # @param character       the character object
    # @param backgroundColor   the new color to apply for the background
    ##
    def __init__(self, character, propertyName, value):
        super().__init__(QCoreApplication.translate("Undo Commands", propertyName))
        
        self.mProperty = propertyName
        if propertyName==AreaPropertyCommand.Icon:
            self.mValue = value.fileName()
        else:
            self.mValue = value
        self.mCharacter = character

    def undo(self):
        self.swap()

    def redo(self):
        self.swap()

    def swap(self):
        # use primitive character object
        character = self.mCharacter.character()
        
        x = self.mProperty
        if x==AreaPropertyCommand.Name:
            character.name, self.mValue = self.mValue, character.name
        elif x==AreaPropertyCommand.Sex:
            character.sex, self.mValue = self.mValue, character.sex
        elif x==AreaPropertyCommand.Icon:
            character.icon, self.mValue = self.mValue, character.icon
        elif x==AreaPropertyCommand.Age:
            character.age, self.mValue = self.mValue, character.age
        elif x==AreaPropertyCommand.Height:
            character.height, self.mValue = self.mValue, character.height
        elif x==AreaPropertyCommand.Weight:
            character.weight, self.mValue = self.mValue, character.weight
        elif x==AreaPropertyCommand.Force:
            character.force, self.mValue = self.mValue, character.force
        elif x==AreaPropertyCommand.Ai:
            character.ai, self.mValue = self.mValue, character.ai
        elif x==AreaPropertyCommand.Scale:
            character.scale, self.mValue = self.mValue, character.scale
        elif x==AreaPropertyCommand.Author:
            character.author, self.mValue = self.mValue, character.author
        elif x==AreaPropertyCommand.Email:
            character.email, self.mValue = self.mValue, character.email
        elif x==AreaPropertyCommand.Description:
            character.description, self.mValue = self.mValue, character.description
        
        self.mCharacter.propertyChanged.emit()
        