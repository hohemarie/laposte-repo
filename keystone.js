var keystone = require('keystone');

keystone.init({
  'cookie secret': 'secure string goes here',
  'name': 'my-project',
  'user model': 'User',
  'auto update': true,
  'auth': true,
  views: 'templates/views',
  'view engine': 'pug',
});

keystone.import('models');

keystone.start();

keystone.set('routes', require('./routes'));
