module.exports = function() {
  this.initConfig({
    latex: {
      src: ['report.tex']
    },
    watch: {
      files: 'report.tex',
      tasks: ['latex', 'shell', 'latex']
    },
    shell: {
      open: {
        command: 'open /Applications/Preview.app report.pdf'
      }
    }
  });
  this.loadNpmTasks('grunt-latex');
  this.loadNpmTasks('grunt-contrib-watch');
  this.loadNpmTasks('grunt-shell');
  this.registerTask('build', ['latex', 'shell', 'latex']);
  return this.registerTask('default', ['build', 'watch']);
};
