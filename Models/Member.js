const sequelize = require('../Database.config/Sequelize');
const bcrypt = require('bcrypt');
const { Sequelize, DataTypes } = require('sequelize');

// Defines the Member model
const Member = sequelize.define('Member', {
 member_id: {
   type: DataTypes.UUID,
   unique: true,
   primaryKey: true,
   defaultValue: Sequelize.UUIDV4,
 },
 member_username: {
   type: DataTypes.STRING,
   unique: true,
   allowNull: false,
 },
 member_password: {
   type: DataTypes.STRING,
   allowNull: false,
 },
}, {
 tableName: 'member',
 timestamps: false,
});

Member.beforeCreate(async (model) => {
    const salt = await bcrypt.genSalt(10);
    model.member_password = await bcrypt.hash(model.member_password, salt);
});

Member.prototype.validPassword = async function(password) {
    return await bcrypt.compare(password, this.member_password);
};

module.exports = Member;